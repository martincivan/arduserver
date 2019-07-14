#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <FastLED.h>

LiquidCrystal_I2C lcd(0x3F,16,2);

#define DATA_PIN 3
#define CLOCK_PIN 13
#define NUM_LEDS 1

CRGB leds[NUM_LEDS];

void printmsg(int row, const char *msg) {
    lcd.setCursor(0, row);
    lcd.print(msg);
//    for(int i=0; i<16 - strlen(msg); i++) {
//      lcd.print(" ");
//    }
}

void setup(void) {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("CAKAM NA PC...");

  FastLED.addLeds<P9813, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
  leds[0] = CHSV(5, 15, 10);
   FastLED.show();
  Serial.print(' ');
}
uint16_t scrollbuf[320];    // my biggest screen is 320x480
#define READGRAM(x, y, buf, w, h)  tft.readGRAM(x, y, buf, w, h)



char* texty[] = {"CPU:%s TEMP:%s", "V1:%s V2:%s", "R:%d G:%d B:%d"};

void citaj(char* kam) {
  int i = 0;
  byte b = Serial.read();
  do {
    kam[i++] = b;
    kam[i]='\0';
    while (!Serial.available()) {
      delay(10);
    }
    b = Serial.read();
  } while(b != 33);
}

void loop(void) {
  if(!Serial.available()){
    return;
  }
  char bafer[17];
  char precitane1[7];
  char precitane2[7];
  byte c = 150;
    citaj(precitane1);
    citaj(precitane2);
    snprintf(bafer, 17, texty[0], precitane1, precitane2);
    printmsg(0, bafer);
    citaj(precitane1);
    citaj(precitane2);
    snprintf(bafer, 17, texty[1], precitane1, precitane2);
    printmsg(1, bafer);

    while (!Serial.available()) {
      delay(10);
    }
    byte r, g, b;
    r = Serial.read();
    while (!Serial.available()) {
      delay(10);
    }
    g = Serial.read();
    while (!Serial.available()) {
      delay(10);
    }
    b = Serial.read();
    snprintf(bafer, 17, texty[2], r, g, b);
    printmsg(1, bafer);
    leds[0] = CHSV(r, g, b);
    FastLED.show();
    Serial.print(' ');
}
