#include <ESP8266WiFi.h> //wifi библиотека
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ElegantOTA.h> //OTA Обновления
#include "FastLED.h"          // библиотека для работы с лентой
#include <EncButton2.h> //библиотека управления кнопками
#include <EEPROM.h>

#define LED_COUNT 85          // число светодиодов в кольце/ленте
#define LED_DT D3             // пин, куда подключен DIN ленты

//Учетные данные wifi
String ssid = "ssid";
String password = "pass";
const char* APssid = "RGBRing";
const char* APpass = "12345678";
String st;//здесь будем хранить найденные wifi сети
ESP8266WebServer server(80); //поднимаем веб сервер на 80 порту

//Подключаем кнопки
EncButton2<EB_BTN> btn1 (INPUT_PULLUP, D1);           // кнопка 1
EncButton2<EB_BTN> btn2 (INPUT_PULLUP, D2);           // кнопка 2
EncButton2<EB_BTN> btn3 (INPUT_PULLUP, D4);           // кнопка 3

int led_bright = 100;          // яркость светодиодов (0 - 255)

unsigned long change_time, last_change, last_bright;

byte ledMode = 0;
/*
  Стартовый режим
  0 - все выключены
  1 - все включены
  3 - кольцевая радуга
*/

// цвета мячиков для режима
byte ballColors[3][3] = {
  {0xff, 0, 0},
  {0xff, 0xff, 0xff},
  {0   , 0   , 0xff}
};

byte cur_color=0;
int red_color=255, green_color=255, blue_color=255;
bool power_flag=false; //флаг включения/выключения питания
// ---------------СЛУЖЕБНЫЕ ПЕРЕМЕННЫЕ-----------------
int BOTTOM_INDEX = 0;        // светодиод начала отсчёта
int TOP_INDEX = int(LED_COUNT / 2);
int EVENODD = LED_COUNT % 2;
struct CRGB leds[LED_COUNT];
int ledsX[LED_COUNT][3];     //-ARRAY FOR COPYING WHATS IN THE LED STRIP CURRENTLY (FOR CELL-AUTOMATA, MARCH, ETC)

int thisdelay = 20;          //-FX LOOPS DELAY VAR
int thisstep = 10;           //-FX LOOPS DELAY VAR
int thishue = 0;             //-FX LOOPS DELAY VAR
int thissat = 255;           //-FX LOOPS DELAY VAR

int thisindex = 0;
int thisRED = 0;
int thisGRN = 0;
int thisBLU = 0;

int idex = 0;                //-LED INDEX (0 to LED_COUNT-1
int ihue = 0;                //-HUE (0-255)
int ibright = 0;             //-BRIGHTNESS (0-255)
int isat = 0;                //-SATURATION (0-255)
int bouncedirection = 0;     //-SWITCH FOR COLOR BOUNCE (0-1)
float tcount = 0.0;          //-INC VAR FOR SIN LOOPS
int lcount = 0;              //-ANOTHER COUNTING VAR

volatile uint32_t btnTimer;
volatile byte modeCounter;
volatile boolean changeFlag;
// ---------------СЛУЖЕБНЫЕ ПЕРЕМЕННЫЕ-----------------
//веб страница


void setup()
{
  
  Serial.begin(115200);              // открыть порт для связи
  //Инициализируем EEPROM
  EEPROM.begin(512); //инициализация
  //читаем параметры из eeprom
  eeprom_read();
  //подключаемся к wifi и поднимаем сервер обновлений
   WiFi.mode(WIFI_AP_STA);
  //создаем точку доступа
  WiFi.softAP(APssid, APpass);
  
  WiFi.begin(ssid.c_str(), password.c_str());
  
  Serial.println("");
  byte tries=10;
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED && tries>0) {
    delay(500);
    Serial.print(".");
    tries--;
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/",handle_main);
  server.on("/onoff",handle_onoff);
  server.on("/change_effect",handle_effect_change);
  server.on("/change_brightness",handle_change_brightness);
  server.on("/change_speed",handle_change_speed);
  server.on("/change_hue",handle_change_hue);
  server.on("/change_color",handle_change_color);
  server.on("/setting",handle_setting);
  server.on("/scan",handle_scan);

  ElegantOTA.begin(&server);    // Стартуем AsyncElegantOTA
  server.begin();
  Serial.println("HTTP server started");
  
  LEDS.setBrightness(led_bright);  // ограничить максимальную яркость

  LEDS.addLeds<WS2811, LED_DT, GRB>(leds, LED_COUNT);  // настрйоки для нашей ленты (ленты на WS2811, WS2812, WS2812B)
  one_color_all(0, 0, 0);          // погасить все светодиоды
  LEDS.show();                     // отослать команду

  randomSeed(analogRead(0));
}

void one_color_all(int cred, int cgrn, int cblu) {       //-SET ALL LEDS TO ONE COLOR
  for (int i = 0 ; i < LED_COUNT; i++ ) {
    leds[i].setRGB( cred, cgrn, cblu);
  }
}

void loop() {
//Опрос кнопок
    btn1.tick();
    btn2.tick();
    btn3.tick();
    button_press();
    server.handleClient();
  switch (ledMode) {
    case 1:  one_color_all(red_color, green_color, blue_color); LEDS.show(); break; //---ALL ON
    case  2: rainbow_fade(); break;            // плавная смена цветов всей ленты
    case  3: rainbow_loop(); break;            // крутящаяся радуга
    case  4: random_burst(); break;            // случайная смена цветов
    case  5: color_bounce(); break;            // бегающий светодиод
    case  6: color_bounceFADE(); break;        // бегающий паровозик светодиодов
    case  7: ems_lightsONE(); break;           // вращаются красный и синий
    case  8: ems_lightsALL(); break;           // вращается половина красных и половина синих
    case  9: flicker(); break;                 // случайный стробоскоп
    case 10: pulse_one_color_all(); break;     // пульсация одним цветом
    case 11: pulse_one_color_all_rev(); break; // пульсация со сменой цветов
    case 12: fade_vertical(); break;           // плавная смена яркости по вертикали (для кольца)
    case 13: rule30(); break;                  // безумие красных светодиодов
    case 14: random_march(); break;            // безумие случайных цветов
    case 15: rwb_march(); break;               // белый синий красный бегут по кругу (ПАТРИОТИЗМ!)
    case 16: RunningLights(0xff, 0xff, 0x00, thisdelay); break;                     // бегущие огни
    case 17: color_loop_vardelay(); break;     // красный светодиод бегает по кругу
    case 18: TwinkleRandom(20, thisdelay, 1); break;                                // случайные разноцветные включения (1 - танцуют все, 0 - случайный 1 диод)
    case 19: quad_bright_curve(); break;       // полумесяц
    case 20: rainbow_vertical(); break;        // радуга в вертикаьной плоскости (кольцо)
    case 21: pacman(); break;                  // пакман
    case 22: flame(); break;                   // эффект пламени
    case 23: random_color_pop(); break;        // безумие случайных вспышек
    case 24: ems_lightsSTROBE(); break;        // полицейская мигалка
    case 25: rgb_propeller(); break;           // RGB пропеллер
    case 26: matrix(); break;                  // зелёненькие бегают по кругу случайно
    case 27: new_rainbow_loop(); break;        // крутая плавная вращающаяся радуга
    case 28: Fire(55, 120, thisdelay); break;                                       // линейный огонь
   
    
  }
}


void change_mode(int newmode) {
  thissat = 255;
  switch (newmode) {
    case 0: one_color_all(0, 0, 0); LEDS.show(); break; //---ALL OFF
    case 1: one_color_all(red_color, green_color, blue_color); LEDS.show(); break; //---ALL ON
    case 2: thisdelay = 60; break;                      //---STRIP RAINBOW FADE
    case 3: thisdelay = 20; thisstep = 10; break;       //---RAINBOW LOOP
    case 4: thisdelay = 20; break;                      //---RANDOM BURST
    case 5: thisdelay = 20; thishue = 0; break;         //---CYLON v1
    case 6: thisdelay = 80; thishue = 0; break;         //---CYLON v2
    case 7: thisdelay = 40; thishue = 0; break;         //---POLICE LIGHTS SINGLE
    case 8: thisdelay = 40; thishue = 0; break;         //---POLICE LIGHTS SOLID
    case 9: thishue = 160; thissat = 50; break;         //---STRIP FLICKER
    case 10: thisdelay = 15; thishue = 0; break;        //---PULSE COLOR BRIGHTNESS
    case 11: thisdelay = 30; thishue = 0; break;        //---PULSE COLOR SATURATION
    case 12: thisdelay = 60; thishue = 180; break;      //---VERTICAL SOMETHING
    case 13: thisdelay = 100; break;                    //---CELL AUTO - RULE 30 (RED)
    case 14: thisdelay = 80; break;                     //---MARCH RANDOM COLORS
    case 15: thisdelay = 80; break;                     //---MARCH RWB COLORS
    case 16: thisdelay = 50; break;                     // RunningLights
    //---PLACEHOLDER FOR COLOR LOOP VAR DELAY VARS
    case 18: thisdelay = 10; break;                     // rainbowTwinkle
    case 19: thisdelay = 100; thishue = 180; break;     //---QUADRATIC BRIGHTNESS CURVE
    //---PLACEHOLDER FOR FLAME VARS
    case 20: thisdelay = 50; thisstep = 15; break;      //---VERITCAL RAINBOW
    case 21: thisdelay = 50; break;                     //---PACMAN
    case 23: thisdelay = 35; break;                     //---RANDOM COLOR POP
    case 24: thisdelay = 25; thishue = 0; break;        //---EMERGECNY STROBE
    case 25: thisdelay = 100; thishue = 0; break;        //---RGB PROPELLER
    case 26: thisdelay = 100; thishue = 95; break;       //---MATRIX RAIN
    case 27: thisdelay = 15; break;                      //---NEW RAINBOW LOOP
    case 28: thisdelay = 15; break;                     // Fire
        
    

    case 101: one_color_all(255, 0, 0); LEDS.show(); break; //---ALL RED
    case 102: one_color_all(0, 255, 0); LEDS.show(); break; //---ALL GREEN
    case 103: one_color_all(0, 0, 255); LEDS.show(); break; //---ALL BLUE
    case 104: one_color_all(255, 255, 0); LEDS.show(); break; //---ALL COLOR X
    case 105: one_color_all(0, 255, 255); LEDS.show(); break; //---ALL COLOR Y
    case 106: one_color_all(255, 0, 255); LEDS.show(); break; //---ALL COLOR Z
  }
  bouncedirection = 0;
  one_color_all(0, 0, 0);
  ledMode = newmode;
}
//выбор действия в зависимости от нажатия кнопки
void button_press()
  
  //Общие настройки для всех режимов
  {
    
    //обработка нажатий первой кнопки
    if (btn1.tick())
    {
      //Кнопка вверх однократное нажатие меняем режим
    if (btn1.click())
      {
        ledMode++;
        if (ledMode>28) ledMode=1; 
        change_mode(ledMode);               // меняем режим через change_mode (там для каждого режима стоят цвета и задержки)    
        changeFlag = true;
        Serial.println(ledMode);
      }

      if (ledMode==1)
      {
        if (btn1.hold())
      {
        switch (cur_color)
          {
            case 0: blue_color+=1;if (red_color<0) red_color=0;Serial.println(red_color); break;
            case 1: green_color+=1;if (green_color<0) green_color=0;Serial.println(green_color); break;
            case 2: blue_color+=1;if (blue_color<0) blue_color=0;Serial.println(blue_color); break;
          }
        }
       
      }
      
    else
    {
    
    //Кнопка вверх удержание увеличиваем яркость
    if (btn1.hold())
      {
        led_bright+=5; //добавляем к значению яркости 5
        if (led_bright>255) //проверяем на выход из диапазона
            {
              led_bright=255;//возвращаем в диапазон
            }
        Serial.println(led_bright);    
        LEDS.setBrightness(led_bright);//устанавливаем новую яркость
      }

      
    }  
    }

    //Обработка нажатий второй кнопки
    if (btn2.tick())
    {
      //Кнопка Питание удержание
    if (btn2.held())
      {
        power_flag =!power_flag;
        if (power_flag) ledMode=1; else ledMode=0;
              change_mode(ledMode);
      }
      //проверяем активный режим
      if (ledMode==1)
      {
        if (btn2.click())
      {
        cur_color++;
        if (cur_color>2) cur_color=0;
        switch (cur_color)
          {
            case 0: one_color_all(255, 0, 0); LEDS.show(); delay (50); break;
            case 1: one_color_all(0, 255, 0); LEDS.show(); delay (50); break;
            case 2: one_color_all(0, 0, 255); LEDS.show(); delay (50); break;
          }
      }
      }
    }

    //Обработка нажатий 3 кнопки
    if (btn3.tick())
    {
      //кнопка вниз однократное нажатие меняем режим
    if (btn3.click())
      {
        ledMode--;
        if (ledMode<1) ledMode=28; 
        change_mode(ledMode);               // меняем режим через change_mode (там для каждого режима стоят цвета и задержки)    
        changeFlag = true;
        Serial.println(ledMode);
      }
      if (ledMode==1)
      {
          if (btn3.hold())
        {
        switch (cur_color)
          {
            case 0: red_color-=1;if (red_color<0) red_color=0;Serial.println(red_color); break;
            case 1: green_color-=1;if (green_color<0) green_color=0;Serial.println(green_color); break;
            case 2: blue_color-=1;if (blue_color<0) blue_color=0;Serial.println(blue_color); break;
          }
        }
      }
    else
    {        
    
      //кнопка вниз удержание меняем яркость
    if (btn3.hold())
      {
        led_bright-=5; //вычитаем из значения яркости 5
        if (led_bright<0) //проверяем на выход из диапазона
            {
              led_bright=0;//возвращаем в диапазон
            }
        Serial.println(led_bright);
        LEDS.setBrightness(led_bright);//устанавливаем новую яркость
      }
     
    }
    }
  }
