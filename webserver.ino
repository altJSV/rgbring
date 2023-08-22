void handle_main()
{
  String page = "<!DOCTYPE HTML><html>";
  page+="<head>";
  page+="<title>Панель управления RGB кольцом</title>";
  page+="<meta name='viewport' content='width=device-width, initial-scale=1'>";
  page+="<meta charset='UTF-8'>";
  page+="<style>";
  page+=".icon-block {position: fixed; top: 1%; right: 2%;}";
  page+=".headerblock {display: flex; width: 80%; color: white; margin: 10px auto 10px auto; flex-direction: column; align-items: center; justify-content: center; background: 	Dodgerblue;}";
  page+=".main {width: 100%; color: black; background: 	Skyblue; font-size: 16px; font-family: sans-serif; font-weight: 700;"; 
  page+=".select-css {width: 100%; display: block; font-size: 16px; font-family: sans-serif; font-weight: 700; color: #444; line-height: 1.3; padding: .6em 1.4em .5em .8em; width: 100%; max-width: 100%;";
  page+="box-sizing: border-box; margin: 0; border: 1px solid #aaa; box-shadow: 0 1px 0 1px rgba(0,0,0,.04); border-radius: .5em;";
  page+="-moz-appearance: none; -webkit-appearance: none; appearance: none; background-color: #fff;"; 
  page+="background-image: url('data:image/svg+xml;charset=US-ASCII,%3Csvg%20xmlns%3D%22http%3A%2F%2Fwww.w3.org%2F2000%2Fsvg%22%20width%3D%22292.4%22%20height%3D%22292.4%22%3E%3Cpath%20fill%3D%22%23007CB2%22%20d%3D%22M287%2069.4a17.6%2017.6%200%200%200-13-5.4H18.4c-5%200-9.3%201.8-12.9%205.4A17.6%2017.6%200%200%200%200%2082.2c0%205%201.8%209.3%205.4%2012.9l128%20127.9c3.6%203.6%207.8%205.4%2012.8%205.4s9.2-1.8%2012.8-5.4L287%2095c3.5-3.5%205.4-7.8%205.4-12.8%200-5-1.9-9.2-5.5-12.8z%22%2F%3E%3C%2Fsvg%3E'), linear-gradient(to bottom, #ffffff 0%,#e5e5e5 100%);"; 
  page+="background-repeat: no-repeat, repeat; background-position: right .7em top 50%, 0 0; background-size: .65em auto, 100%;}";
  page+=".slider {-webkit-appearance: none; appearance: none; width: 100%; height: 25px; background: #d3d3d3; outline: none; opacity: 0.7; -webkit-transition: .2s; transition: opacity .2s;}";
  page+=".slider:hover { opacity: 1;}";
  page+=".slider::-webkit-slider-thumb {-webkit-appearance: none; appearance: none; width: 25px; height: 25px; background: Dodgerblue; cursor: pointer;}";
  page+=".slider::-moz-range-thumb {width: 25px; height: 25px; background: Dodgerblue; cursor: pointer;}";  
  page+=".icon{fill: #000000;}";
  page+="</style>";
  page+="<script type='text/javascript'>";
  page+="function change_effect(){";
  page+="const select = document.getElementById('efnum');";
  page+="var valeffect=select.value;";
  page+="var server = '/change_effect?val='+valeffect;";
  page+="request = new XMLHttpRequest();";
  page+="request.open('GET',server, true);";
  page+="request.send();}";
  page+="function change_brightness(){";
  page+="const bright = document.getElementById('bright');";
  page+="var valbright=bright.value;";
  page+="var server = '/change_brightness?val='+valbright;";
  page+="request = new XMLHttpRequest();";
  page+="request.open('GET',server, true);";
  page+="request.send();}";  
  page+="function change_color(){";
  page+="const redc = document.getElementById('redsl');";
  page+="const greenc = document.getElementById('greensl');";
  page+="const bluec = document.getElementById('bluesl');";
  page+="var valred=redc.value;";
  page+="var valgreen=greenc.value;";
  page+="var valblue=bluec.value;";
  page+="var server = '/change_color?red='+valred+'&green='+valgreen+'&blue='+valblue;";
  page+="request = new XMLHttpRequest();";
  page+="request.open('GET',server, true);";
  page+="request.send();}";  
  page+="</script>";
  page+="</head>";
  page+="<body>";
  page+="<h1 align='center'>Панель управления RGB кольцом</h1>";
  page+="<div class='headerblock'>";
  page+="<h2>Выбор эффекта</h2>";
  page+="<div class='main'>";
  page+="<p>Выберите эффект подсветки из выпадающего списка</p>";
  page+="<select  class= 'select-css' name='efnum' id='efnum' width='80%' align='center' onchange='change_effect()'>";
  page+="<option value='1'>Выбор одного цвета</option>";
  page+="<option value='2'>Плавная смена цветов всей ленты</option>";
  page+="<option value='3'>Крутящаяся радуга</option>";
  page+="<option value='4'>случайная смена цветов</option>";
  page+="<option value='5'>Бегающий светодиод</option>";
  page+="<option value='6'>Бегающий паровозик светодиодов</option>";
  page+="<option value='7'>Вращаются красный и синий</option>";
  page+="<option value='8'>Вращается половина красных и половина синих</option>";
  page+="<option value='9'>Случайный стробоскоп</option>";
  page+="<option value='10'>Пульсация одним цветом</option>";
  page+="<option value='11'>Пульсация со сменой цветов</option>";
  page+="<option value='12'>Плавная смена яркости</option>";
  page+="<option value='13'>Безумие красных светодиодов</option>";
  page+="<option value='14'>Безумие случайных цветов</option>";
  page+="<option value='15'>Белый синий красный бегут по кругу</option>";
  page+="<option value='16'>Бегущие огни</option>";
  page+="<option value='17'>Красный светодиод бегает по кругу</option>";
  page+="<option value='19'>Полумесяц</option>";
  page+="<option value='20'>Радуга</option>";
  page+="<option value='21'>Пакман</option>";
  page+="<option value='22'>Эффект пламени</option>";
  page+="<option value='23'>Безумие случайных вспышек</option>";
  page+="<option value='24'>Полицейская мигалка</option>";
  page+="<option value='25'>RGB пропеллер</option>";
  page+="<option value='26'>Зелёненькие бегают по кругу случайно</option>";
  page+="<option value='27'>Крутая плавная вращающаяся радуга</option>";
  page+="<option value='28'>Плавное заполнение цветом</option>";
  page+="<option value='29'>Бегающие светодиоды</option>";
  page+="<option value='30'>Линейный огонь</option>";
  page+="<option value='31'>Очень плавная вращающаяся радуга</option>";
  page+="</select>";
  page+="</div></div>";
  page+="<div class='headerblock'>";
  page+="<h2>Настройка яркости</h2>";
  page+="<div class='main'>";
  page+="<p>Установите с помощью слайдера яркость светодиодов</p>";
  page+="<input id='bright' type='range' class='slider' min='0' max='255' step='1' width='100%' align='center' value='"+String(led_bright)+"'  onchange='change_brightness()'>";
  page+="</div></div>";
  /* пока данный код глючит. Оставим до будущих релизов*/
  page+="<div class='headerblock'>";
  page+="<h2>Настройка цветовой палитры для режима одного цвета</h2>";
  page+="<div class='main'>";
  page+="<p>Для режима одного цвета установите значение каждого из цветов</p>";
  page+="<p><font color='red'>Интенсивность красного цвета</font>";
  page+="<input id='redsl' type='range' class='slider' min='0' max='255' step='1' width='100%' align='center' value='"+String(red_color)+"' onchange='change_color()'></p>";
  page+="<p><font color='green'>Интенсивность зеленого цвета</font>";
  page+="<input id='greensl' type='range' class='slider' min='0' max='255' step='1' width='100%' align='center' value='"+String(green_color)+"' onchange='change_color()'></p>";
  page+="<p><font color='blue'>Интенсивность синего цвета</font>";
  page+="<input id='bluesl' type='range' class='slider' min='0' max='255' step='1' width='100%' align='center' value='"+String(blue_color)+"' onchange='change_color()'></p>";
  page+="</div></div>";
  
  page+="<div class='icon-block'><a href='/update'><svg class='icon' width='50' height='50' fill='none' xmlns='http://www.w3.org/2000/svg'>";
  page+="<g id='SVGRepo_bgCarrier' stroke-width='0'></g><g id='SVGRepo_tracerCarrier' stroke-linecap='round' stroke-linejoin='round'></g><g id='SVGRepo_iconCarrier'><path id='primary' d='M6,5H16a2,2,0,0,1,2,2v7' style='fill: none; stroke: #000000; stroke-linecap: round; stroke-linejoin: round; stroke-width: 2;'></path><path id='primary-2' data-name='primary' d='M18,19H8a2,2,0,0,1-2-2V10' style='fill: none; stroke: #000000; stroke-linecap: round; stroke-linejoin: round; stroke-width: 2;'></path><polyline id='primary-3' data-name='primary' points='15 11 18 14 21 11' style='fill: none; stroke: #000000; stroke-linecap: round; stroke-linejoin: round; stroke-width: 2;'></polyline><polyline id='primary-4' data-name='primary' points='9 13 6 10 3 13' style='fill: none; stroke: #000000; stroke-linecap: round; stroke-linejoin: round; stroke-width: 2;'></polyline></g></svg>";
  page+="<a href='/onoff'><svg class='icon' width='50' height='50' fill='none' xmlns='http://www.w3.org/2000/svg'>";
  page+="<path d='M12 3V12M18.3611 5.64001C19.6195 6.8988 20.4764 8.50246 20.8234 10.2482C21.1704 11.994 20.992 13.8034 20.3107 15.4478C19.6295 17.0921 18.4759 18.4976 16.9959 19.4864C15.5159 20.4752 13.776 21.0029 11.9961 21.0029C10.2162 21.0029 8.47625 20.4752 6.99627 19.4864C5.51629 18.4976 4.36274 17.0921 3.68146 15.4478C3.00019 13.8034 2.82179 11.994 3.16882 10.2482C3.51584 8.50246 4.37272 6.8988 5.6311 5.64001' stroke='#000000' stroke-width='2' stroke-linecap='round' stroke-linejoin='round'></path>";
  page+="</svg></a> </div>";
  page+="</body>";
  page+="</html>";
server.send(200, "text/html", page); 
}
//включение и вуключение лампы в веб интерфейсе
void handle_onoff()
{
  power_flag =!power_flag;
  if (power_flag) ledMode=1; else ledMode=0;
  change_mode(ledMode);
  server.sendHeader("Location", "/",true);   //редирект на главную
  server.send(302, "text/plane","");
}

//смена эффекта в веб интерфейсе
void handle_effect_change()
{
  ledMode = server.arg("val").toInt();
  change_mode(ledMode);               // меняем режим через change_mode (там для каждого режима стоят цвета и задержки)    
  changeFlag = true;
  Serial.println(ledMode);
  server.sendHeader("Location", "/",true);   //редирект на главную
  server.send(302, "text/plane","");
}

//Изменение яркости в веб интерфейсе
void handle_change_brightness()
{
  led_bright = server.arg("val").toInt();
  LEDS.setBrightness(led_bright);//устанавливаем новую яркость
  Serial.println(led_bright);
  server.sendHeader("Location", "/",true);   //редирект на главную
  server.send(302, "text/plane","");
}

//Изменение цвета в веб интерфейсе
void handle_change_color()
{
  red_color = server.arg("red").toInt();
  green_color = server.arg("green").toInt();
  blue_color = server.arg("blue").toInt();
  change_mode(1); 
  server.sendHeader("Location", "/",true);   //редирект на главную
  server.send(302, "text/plane","");
}