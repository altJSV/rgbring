//------------------------LED EFFECT FUNCTIONS------------------------


void one_color_allHSV(int ahue) {    //-SET ALL LEDS TO ONE COLOR (HSV)
  for (int i = 0 ; i < LED_COUNT; i++ ) {
    leds[i] = CHSV(ahue, thissat, 255);
  }
}

void rainbow_fade() {                         //-m2-FADE ALL LEDS THROUGH HSV RAINBOW
  ihue++;
  if (ihue > 255) {
    ihue = 0;
  }
  for (int idex = 0 ; idex < LED_COUNT; idex++ ) {
    leds[idex] = CHSV(ihue, thissat, 255);
  }
  LEDS.show();
  if (safeDelay(thisdelay)) return;
}

void rainbow_loop() {                        //-m3-LOOP HSV RAINBOW
  idex++;
  ihue = ihue + thisstep;
  if (idex >= LED_COUNT) {
    idex = 0;
  }
  if (ihue > 255) {
    ihue = 0;
  }
  leds[idex] = CHSV(ihue, thissat, 255);
  LEDS.show();
  if (safeDelay(thisdelay)) return;
}

void random_burst() {                         //-m4-RANDOM INDEX/COLOR
  idex = random(0, LED_COUNT);
  ihue = random(0, 255);
  leds[idex] = CHSV(ihue, thissat, 255);
  LEDS.show();
  if (safeDelay(thisdelay)) return;
}

void color_bounce() {                        //-m5-BOUNCE COLOR (SINGLE LED)
  if (bouncedirection == 0) {
    idex = idex + 1;
    if (idex == LED_COUNT) {
      bouncedirection = 1;
      idex = idex - 1;
    }
  }
  if (bouncedirection == 1) {
    idex = idex - 1;
    if (idex == 0) {
      bouncedirection = 0;
    }
  }
  for (int i = 0; i < LED_COUNT; i++ ) {
    if (i == idex) {
      leds[i] = CHSV(thishue, thissat, 255);
    }
    else {
      leds[i] = CHSV(0, 0, 0);
    }
  }
  LEDS.show();
  if (safeDelay(thisdelay)) return;
}

void color_bounceFADE() {                    //-m6-BOUNCE COLOR (SIMPLE MULTI-LED FADE)
  if (bouncedirection == 0) {
    idex = idex + 1;
    if (idex == LED_COUNT) {
      bouncedirection = 1;
      idex = idex - 1;
    }
  }
  if (bouncedirection == 1) {
    idex = idex - 1;
    if (idex == 0) {
      bouncedirection = 0;
    }
  }
  int iL1 = adjacent_cw(idex);
  int iL2 = adjacent_cw(iL1);
  int iL3 = adjacent_cw(iL2);
  int iR1 = adjacent_ccw(idex);
  int iR2 = adjacent_ccw(iR1);
  int iR3 = adjacent_ccw(iR2);
  for (int i = 0; i < LED_COUNT; i++ ) {
    if (i == idex) {
      leds[i] = CHSV(thishue, thissat, 255);
    }
    else if (i == iL1) {
      leds[i] = CHSV(thishue, thissat, 150);
    }
    else if (i == iL2) {
      leds[i] = CHSV(thishue, thissat, 80);
    }
    else if (i == iL3) {
      leds[i] = CHSV(thishue, thissat, 20);
    }
    else if (i == iR1) {
      leds[i] = CHSV(thishue, thissat, 150);
    }
    else if (i == iR2) {
      leds[i] = CHSV(thishue, thissat, 80);
    }
    else if (i == iR3) {
      leds[i] = CHSV(thishue, thissat, 20);
    }
    else {
      leds[i] = CHSV(0, 0, 0);
    }
  }
  LEDS.show();
  if (safeDelay(thisdelay)) return;
}

void ems_lightsONE() {                    //-m7-EMERGENCY LIGHTS (TWO COLOR SINGLE LED)
  idex++;
  if (idex >= LED_COUNT) {
    idex = 0;
  }
  int idexR = idex;
  int idexB = antipodal_index(idexR);
  int thathue = (thishue + 160) % 255;
  for (int i = 0; i < LED_COUNT; i++ ) {
    if (i == idexR) {
      leds[i] = CHSV(thishue, thissat, 255);
    }
    else if (i == idexB) {
      leds[i] = CHSV(thathue, thissat, 255);
    }
    else {
      leds[i] = CHSV(0, 0, 0);
    }
  }
  LEDS.show();
  if (safeDelay(thisdelay)) return;
}

void ems_lightsALL() {                  //-m8-EMERGENCY LIGHTS (TWO COLOR SOLID)
  idex++;
  if (idex >= LED_COUNT) {
    idex = 0;
  }
  int idexR = idex;
  int idexB = antipodal_index(idexR);
  int thathue = (thishue + 160) % 255;
  leds[idexR] = CHSV(thishue, thissat, 255);
  leds[idexB] = CHSV(thathue, thissat, 255);
  LEDS.show();
  if (safeDelay(thisdelay)) return;
}

void flicker() {                          //-m9-FLICKER EFFECT
  int random_bright = random(0, 255);
  int random_delay = random(10, 100);
  int random_bool = random(0, random_bright);
  if (random_bool < 10) {
    for (int i = 0 ; i < LED_COUNT; i++ ) {
      leds[i] = CHSV(thishue, thissat, random_bright);
    }
    LEDS.show();
    if (safeDelay(random_delay)) return;
  }
}

void pulse_one_color_all() {              //-m10-PULSE BRIGHTNESS ON ALL LEDS TO ONE COLOR
  if (bouncedirection == 0) {
    ibright++;
    if (ibright >= 255) {
      bouncedirection = 1;
    }
  }
  if (bouncedirection == 1) {
    ibright = ibright - 1;
    if (ibright <= 1) {
      bouncedirection = 0;
    }
  }
  for (int idex = 0 ; idex < LED_COUNT; idex++ ) {
    leds[idex] = CHSV(thishue, thissat, ibright);
  }
  LEDS.show();
  if (safeDelay(thisdelay)) return;
}

void pulse_one_color_all_rev() {           //-m11-PULSE SATURATION ON ALL LEDS TO ONE COLOR
  if (bouncedirection == 0) {
    isat++;
    if (isat >= 255) {
      bouncedirection = 1;
    }
  }
  if (bouncedirection == 1) {
    isat = isat - 1;
    if (isat <= 1) {
      bouncedirection = 0;
    }
  }
  for (int idex = 0 ; idex < LED_COUNT; idex++ ) {
    leds[idex] = CHSV(thishue, isat, 255);
  }
  LEDS.show();
  if (safeDelay(thisdelay)) return;
}

void fade_vertical() {                    //-m12-FADE 'UP' THE LOOP
  idex++;
  if (idex > TOP_INDEX) {
    idex = 0;
  }
  int idexA = idex;
  int idexB = horizontal_index(idexA);
  ibright = ibright + 10;
  if (ibright > 255) {
    ibright = 0;
  }
  leds[idexA] = CHSV(thishue, thissat, ibright);
  leds[idexB] = CHSV(thishue, thissat, ibright);
  LEDS.show();
  if (safeDelay(thisdelay)) return;
}

void random_red() {                       //QUICK 'N DIRTY RANDOMIZE TO GET CELL AUTOMATA STARTED
  int temprand;
  for (int i = 0; i < LED_COUNT; i++ ) {
    temprand = random(0, 100);
    if (temprand > 50) {
      leds[i].r = 255;
    }
    if (temprand <= 50) {
      leds[i].r = 0;
    }
    leds[i].b = 0; leds[i].g = 0;
  }
  LEDS.show();
}

void rule30() {                          //-m13-1D CELLULAR AUTOMATA - RULE 30 (RED FOR NOW)
  if (bouncedirection == 0) {
    random_red();
    bouncedirection = 1;
  }
  copy_led_array();
  int iCW;
  int iCCW;
  int y = 100;
  for (int i = 0; i < LED_COUNT; i++ ) {
    iCW = adjacent_cw(i);
    iCCW = adjacent_ccw(i);
    if (ledsX[iCCW][0] > y && ledsX[i][0] > y && ledsX[iCW][0] > y) {
      leds[i].r = 0;
    }
    if (ledsX[iCCW][0] > y && ledsX[i][0] > y && ledsX[iCW][0] <= y) {
      leds[i].r = 0;
    }
    if (ledsX[iCCW][0] > y && ledsX[i][0] <= y && ledsX[iCW][0] > y) {
      leds[i].r = 0;
    }
    if (ledsX[iCCW][0] > y && ledsX[i][0] <= y && ledsX[iCW][0] <= y) {
      leds[i].r = 255;
    }
    if (ledsX[iCCW][0] <= y && ledsX[i][0] > y && ledsX[iCW][0] > y) {
      leds[i].r = 255;
    }
    if (ledsX[iCCW][0] <= y && ledsX[i][0] > y && ledsX[iCW][0] <= y) {
      leds[i].r = 255;
    }
    if (ledsX[iCCW][0] <= y && ledsX[i][0] <= y && ledsX[iCW][0] > y) {
      leds[i].r = 255;
    }
    if (ledsX[iCCW][0] <= y && ledsX[i][0] <= y && ledsX[iCW][0] <= y) {
      leds[i].r = 0;
    }
  }
  LEDS.show();
  if (safeDelay(thisdelay)) return;
}

void random_march() {                   //-m14-RANDOM MARCH CCW
  copy_led_array();
  int iCCW;
  leds[0] = CHSV(random(0, 255), 255, 255);
  for (int idex = 1; idex < LED_COUNT ; idex++ ) {
    iCCW = adjacent_ccw(idex);
    leds[idex].r = ledsX[iCCW][0];
    leds[idex].g = ledsX[iCCW][1];
    leds[idex].b = ledsX[iCCW][2];
  }
  LEDS.show();
  if (safeDelay(thisdelay)) return;
}

void rwb_march() {                    //-m15-R,W,B MARCH CCW
  copy_led_array();
  int iCCW;
  idex++;
  if (idex > 2) {
    idex = 0;
  }
  switch (idex) {
    case 0:
      leds[0].r = 255;
      leds[0].g = 0;
      leds[0].b = 0;
      break;
    case 1:
      leds[0].r = 255;
      leds[0].g = 255;
      leds[0].b = 255;
      break;
    case 2:
      leds[0].r = 0;
      leds[0].g = 0;
      leds[0].b = 255;
      break;
  }
  for (int i = 1; i < LED_COUNT; i++ ) {
    iCCW = adjacent_ccw(i);
    leds[i].r = ledsX[iCCW][0];
    leds[i].g = ledsX[iCCW][1];
    leds[i].b = ledsX[iCCW][2];
  }
  LEDS.show();
  if (safeDelay(thisdelay)) return;
}


void color_loop_vardelay() {                    //-m17-COLOR LOOP (SINGLE LED) w/ VARIABLE DELAY
  idex++;
  if (idex > LED_COUNT) {
    idex = 0;
  }
  int di = abs(TOP_INDEX - idex);
  int t = constrain((10 / di) * 10, 10, 500);
  for (int i = 0; i < LED_COUNT; i++ ) {
    if (i == idex) {
      leds[i] = CHSV(0, thissat, 255);
    }
    else {
      leds[i].r = 0; leds[i].g = 0; leds[i].b = 0;
    }
  }
  LEDS.show();
  if (safeDelay(t)) return;
}

void quad_bright_curve() {      //-m21-QUADRATIC BRIGHTNESS CURVER
  int ax;
  for (int x = 0; x < LED_COUNT; x++ ) {
    if (x <= TOP_INDEX) {
      ax = x;
    }
    else if (x > TOP_INDEX) {
      ax = LED_COUNT - x;
    }
    int a = 1; int b = 1; int c = 0;
    int iquad = -(ax * ax * a) + (ax * b) + c; //-ax2+bx+c
    int hquad = -(TOP_INDEX * TOP_INDEX * a) + (TOP_INDEX * b) + c;
    ibright = int((float(iquad) / float(hquad)) * 255);
    leds[x] = CHSV(thishue, thissat, ibright);
  }
  LEDS.show();
  if (safeDelay(thisdelay)) return;
}

void flame() {                                    //-m22-FLAMEISH EFFECT
  int idelay = random(0, 35);
  float hmin = 0.1; float hmax = 45.0;
  float hdif = hmax - hmin;
  int randtemp = random(0, 3);
  float hinc = (hdif / float(TOP_INDEX)) + randtemp;
  int ihue = hmin;
  for (int i = 0; i <= TOP_INDEX; i++ ) {
    ihue = ihue + hinc;
    leds[i] = CHSV(ihue, thissat, 255);
    int ih = horizontal_index(i);
    leds[ih] = CHSV(ihue, thissat, 255);
    leds[TOP_INDEX].r = 255; leds[TOP_INDEX].g = 255; leds[TOP_INDEX].b = 255;
    LEDS.show();
    if (safeDelay(idelay)) return;
  }
}

void rainbow_vertical() {                        //-m23-RAINBOW 'UP' THE LOOP
  idex++;
  if (idex > TOP_INDEX) {
    idex = 0;
  }
  ihue = ihue + thisstep;
  if (ihue > 255) {
    ihue = 0;
  }
  int idexA = idex;
  int idexB = horizontal_index(idexA);
  leds[idexA] = CHSV(ihue, thissat, 255);
  leds[idexB] = CHSV(ihue, thissat, 255);
  LEDS.show();
  if (safeDelay(thisdelay)) return;
}

void pacman() {                                  //-m24-REALLY TERRIBLE PACMAN CHOMPING EFFECT
  int s = int(LED_COUNT / 4);
  lcount++;
  if (lcount > 5) {
    lcount = 0;
  }
  if (lcount == 0) {
    for (int i = 0 ; i < LED_COUNT; i++ ) {
      set_color_led(i, 255, 255, 0);
    }
  }
  if (lcount == 1 || lcount == 5) {
    for (int i = 0 ; i < LED_COUNT; i++ ) {
      set_color_led(i, 255, 255, 0);
    }
    leds[s].r = 0; leds[s].g = 0; leds[s].b = 0;
  }
  if (lcount == 2 || lcount == 4) {
    for (int i = 0 ; i < LED_COUNT; i++ ) {
      set_color_led(i, 255, 255, 0);
    }
    leds[s - 1].r = 0; leds[s - 1].g = 0; leds[s - 1].b = 0;
    leds[s].r = 0; leds[s].g = 0; leds[s].b = 0;
    leds[s + 1].r = 0; leds[s + 1].g = 0; leds[s + 1].b = 0;
  }
  if (lcount == 3) {
    for (int i = 0 ; i < LED_COUNT; i++ ) {
      set_color_led(i, 255, 255, 0);
    }
    leds[s - 2].r = 0; leds[s - 2].g = 0; leds[s - 2].b = 0;
    leds[s - 1].r = 0; leds[s - 1].g = 0; leds[s - 1].b = 0;
    leds[s].r = 0; leds[s].g = 0; leds[s].b = 0;
    leds[s + 1].r = 0; leds[s + 1].g = 0; leds[s + 1].b = 0;
    leds[s + 2].r = 0; leds[s + 2].g = 0; leds[s + 2].b = 0;
  }
  LEDS.show();
  if (safeDelay(thisdelay)) return;
}

void random_color_pop() {                         //-m25-RANDOM COLOR POP
  idex = random(0, LED_COUNT);
  ihue = random(0, 255);
  one_color_all(0, 0, 0);
  leds[idex] = CHSV(ihue, thissat, 255);
  LEDS.show();
  if (safeDelay(thisdelay)) return;
}

void ems_lightsSTROBE() {                  //-m26-EMERGENCY LIGHTS (STROBE LEFT/RIGHT)
  int thishue = 0;
  int thathue = (thishue + 160) % 255;
  for (int x = 0 ; x < 5; x++ ) {
    for (int i = 0 ; i < TOP_INDEX; i++ ) {
      leds[i] = CHSV(thishue, thissat, 255);
    }
    LEDS.show(); if (safeDelay(thisdelay)) return;
    one_color_all(0, 0, 0);
    LEDS.show(); if (safeDelay(thisdelay)) return;
  }
  for (int x = 0 ; x < 5; x++ ) {
    for (int i = TOP_INDEX ; i < LED_COUNT; i++ ) {
      leds[i] = CHSV(thathue, thissat, 255);
    }
    LEDS.show(); if (safeDelay(thisdelay)) return;
    one_color_all(0, 0, 0);
    LEDS.show(); if (safeDelay(thisdelay)) return;
  }
}

void rgb_propeller() {                           //-m27-RGB PROPELLER
  idex++;
  int ghue = (thishue + 80) % 255;
  int bhue = (thishue + 160) % 255;
  int N3  = int(LED_COUNT / 3);
  int N6  = int(LED_COUNT / 6);
  int N12 = int(LED_COUNT / 12);
  for (int i = 0; i < N3; i++ ) {
    int j0 = (idex + i + LED_COUNT - N12) % LED_COUNT;
    int j1 = (j0 + N3) % LED_COUNT;
    int j2 = (j1 + N3) % LED_COUNT;
    leds[j0] = CHSV(thishue, thissat, 255);
    leds[j1] = CHSV(ghue, thissat, 255);
    leds[j2] = CHSV(bhue, thissat, 255);
  }
  LEDS.show();
  if (safeDelay(thisdelay)) return;
}


void matrix() {                                   //-m29-ONE LINE MATRIX
  int rand = random(0, 100);
  if (rand > 90) {
    leds[0] = CHSV(thishue, thissat, 255);
  }
  else {
    leds[0] = CHSV(thishue, thissat, 0);
  }
  copy_led_array();
  for (int i = 1; i < LED_COUNT; i++ ) {
    leds[i].r = ledsX[i - 1][0];
    leds[i].g = ledsX[i - 1][1];
    leds[i].b = ledsX[i - 1][2];
  }
  LEDS.show();
  if (safeDelay(thisdelay)) return;
}


void new_rainbow_loop() {                      //-m88-RAINBOW FADE FROM FAST_SPI2
  ihue -= 1;
  fill_rainbow( leds, LED_COUNT, ihue );
  LEDS.show();
  if (safeDelay(thisdelay)) return;
}


//---------------------------------линейный огонь-------------------------------------
void Fire(int Cooling, int Sparking, int SpeedDelay) {
  static byte heat[LED_COUNT];
  int cooldown;

  // Step 1.  Cool down every cell a little
  for ( int i = 0; i < LED_COUNT; i++) {
    cooldown = random(0, ((Cooling * 10) / LED_COUNT) + 2);

    if (cooldown > heat[i]) {
      heat[i] = 0;
    } else {
      heat[i] = heat[i] - cooldown;
    }
  }

  // Step 2.  Heat from each cell drifts 'up' and diffuses a little
  for ( int k = LED_COUNT - 1; k >= 2; k--) {
    heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
  }

  // Step 3.  Randomly ignite new 'sparks' near the bottom
  if ( random(255) < Sparking ) {
    int y = random(7);
    heat[y] = heat[y] + random(160, 255);
    //heat[y] = random(160,255);
  }

  // Step 4.  Convert heat to LED colors
  for ( int j = 0; j < LED_COUNT; j++) {
    setPixelHeatColor(j, heat[j] );
  }

  FastLED.show();
  if (safeDelay(SpeedDelay)) return;
}

void setPixelHeatColor (int Pixel, byte temperature) {
  // Scale 'heat' down from 0-255 to 0-191
  byte t192 = round((temperature / 255.0) * 191);

  // calculate ramp up from
  byte heatramp = t192 & 0x3F; // 0..63
  heatramp <<= 2; // scale up to 0..252

  // figure out which third of the spectrum we're in:
  if ( t192 > 0x80) {                    // hottest
    setPixel(Pixel, 255, 255, heatramp);
  } else if ( t192 > 0x40 ) {            // middle
    setPixel(Pixel, 255, heatramp, 0);
  } else {                               // coolest
    setPixel(Pixel, heatramp, 0, 0);
  }
}


void CenterToOutside(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay) {
  for (int i = ((LED_COUNT - EyeSize) / 2); i >= 0; i--) {
    setAll(0, 0, 0);

    setPixel(i, red / 10, green / 10, blue / 10);
    for (int j = 1; j <= EyeSize; j++) {
      setPixel(i + j, red, green, blue);
    }
    setPixel(i + EyeSize + 1, red / 10, green / 10, blue / 10);

    setPixel(LED_COUNT - i, red / 10, green / 10, blue / 10);
    for (int j = 1; j <= EyeSize; j++) {
      setPixel(LED_COUNT - i - j, red, green, blue);
    }
    setPixel(LED_COUNT - i - EyeSize - 1, red / 10, green / 10, blue / 10);

    FastLED.show();
    if (safeDelay(SpeedDelay)) return;
  }
  if (safeDelay(ReturnDelay)) return;
}

void OutsideToCenter(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay) {
  for (int i = 0; i <= ((LED_COUNT - EyeSize) / 2); i++) {
    setAll(0, 0, 0);

    setPixel(i, red / 10, green / 10, blue / 10);
    for (int j = 1; j <= EyeSize; j++) {
      setPixel(i + j, red, green, blue);
    }
    setPixel(i + EyeSize + 1, red / 10, green / 10, blue / 10);

    setPixel(LED_COUNT - i, red / 10, green / 10, blue / 10);
    for (int j = 1; j <= EyeSize; j++) {
      setPixel(LED_COUNT - i - j, red, green, blue);
    }
    setPixel(LED_COUNT - i - EyeSize - 1, red / 10, green / 10, blue / 10);

    FastLED.show();
    if (safeDelay(SpeedDelay)) return;
  }
  if (safeDelay(ReturnDelay)) return;
}

void LeftToRight(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay) {
  for (int i = 0; i < LED_COUNT - EyeSize - 2; i++) {
    setAll(0, 0, 0);
    setPixel(i, red / 10, green / 10, blue / 10);
    for (int j = 1; j <= EyeSize; j++) {
      setPixel(i + j, red, green, blue);
    }
    setPixel(i + EyeSize + 1, red / 10, green / 10, blue / 10);
    FastLED.show();
    if (safeDelay(SpeedDelay)) return;
  }
  if (safeDelay(ReturnDelay)) return;
}

void RightToLeft(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay) {
  for (int i = LED_COUNT - EyeSize - 2; i > 0; i--) {
    setAll(0, 0, 0);
    setPixel(i, red / 10, green / 10, blue / 10);
    for (int j = 1; j <= EyeSize; j++) {
      setPixel(i + j, red, green, blue);
    }
    setPixel(i + EyeSize + 1, red / 10, green / 10, blue / 10);
    FastLED.show();
    if (safeDelay(SpeedDelay)) return;
  }
  if (safeDelay(ReturnDelay)) return;
}


//-------------------------------TwinkleRandom---------------------------------------
void TwinkleRandom(int Count, int SpeedDelay, boolean OnlyOne) {
  setAll(0, 0, 0);

  for (int i = 0; i < Count; i++) {
    setPixel(random(LED_COUNT), random(0, 255), random(0, 255), random(0, 255));
    FastLED.show();
    if (safeDelay(SpeedDelay)) return;
    if (OnlyOne) {
      setAll(0, 0, 0);
    }
  }

  if (safeDelay(SpeedDelay)) return;
}

//-------------------------------RunningLights---------------------------------------
void RunningLights(byte red, byte green, byte blue, int WaveDelay) {
  int Position = 0;

  for (int i = 0; i < LED_COUNT * 2; i++)
  {
    Position++; // = 0; //Position + Rate;
    for (int i = 0; i < LED_COUNT; i++) {
      // sine wave, 3 offset waves make a rainbow!
      //float level = sin(i+Position) * 127 + 128;
      //setPixel(i,level,0,0);
      //float level = sin(i+Position) * 127 + 128;
      setPixel(i, ((sin(i + Position) * 127 + 128) / 255)*red,
               ((sin(i + Position) * 127 + 128) / 255)*green,
               ((sin(i + Position) * 127 + 128) / 255)*blue);
    }

    FastLED.show();
    if (safeDelay(WaveDelay)) return;
  }
}


boolean safeDelay(int delTime) {
  uint32_t thisTime = millis();
  while (millis() - thisTime <= delTime) {
    if (changeFlag) {
      changeFlag = false;
      return true;
    }
  }
  return false;
}
