#include <FastLED.h>

#define    NUM_LEDS             1      // P9813 module: string is one l
#define DATA_PIN 3
#define CLOCK_PIN 13
CRGB leds[NUM_LEDS];


void setup() {
    LEDS.addLeds<P9813, DATA_PIN, CLOCK_PIN>(leds, NUM_LEDS);  // initialize LED control object
    Serial.begin(9600);
//    Serial.println("");
//    Serial.println();
}

//============

byte cg, smer;
void cakanie() {
  if (cg > 150) {
    Serial.println("f");
    smer = 0;
  }
  if (cg < 10) {
        Serial.println("f");
    smer = 2;
  }
  cg += (smer-1);
  leds[0].setRGB(0, cg, 0);
  FastLED.show();
}

int timeout = 0;
void loop() {
  
   if (Serial.available()) {
    timeout = 0;
    byte r, g, b;
    r = Serial.read();
    while (!Serial.available() && timeout < 2000) {
      delay(10);
      timeout++;
    }
    g = Serial.read();
    while (!Serial.available() && timeout < 2000) {
      delay(10);
      timeout++;
    }
    b = Serial.read();
    leds[0].setRGB(r, g, b);
    FastLED.show();
    Serial.write("f");
   } else {
    timeout++;
    delay(10);
   }
   if (timeout > 2000) {
    cakanie();
    delay(100);
   }
}
