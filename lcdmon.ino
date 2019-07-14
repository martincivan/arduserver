#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0
#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

#include <SPI.h>          // f.k. for Arduino-1.5.2
#include "Adafruit_GFX.h"// Hardware-specific library
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;
#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

#ifndef min
#define min(a, b) (((a) < (b)) ? (a) : (b))
#endif
void printmsg(int row, const char *msg) {
    tft.setTextColor(YELLOW, BLACK);
    tft.setCursor(0, row);
    tft.print(msg);
    for(int i=0; i<30 - strlen(msg); i++) {
      tft.print(" ");
    }
}

void setup(void) {
    Serial.begin(9600);
    uint16_t ID = tft.readID(); //
    if (ID == 0xD3D3) ID = 0x9481; // write-only shield
//    ID = 0x9329;                             // force ID
    tft.begin(ID);
    tft.setTextSize(2);
    tft.fillRect(0, 0, 320, 480, 0);
    printmsg(0, "CAKAM NA PC...");
}
uint16_t scrollbuf[320];    // my biggest screen is 320x480
#define READGRAM(x, y, buf, w, h)  tft.readGRAM(x, y, buf, w, h)



char* texty[] = {"CPU FREKVENCIA: %sMHz", "TDIE: %sC", "TCTL: %sC", "VENTILATOR 1: %sRPM/s", "VENTILATOR 2: %sRPM/s"};

void loop(void) {
  if(!Serial.available()){
    return;
  }
  char bafer[32];
  char precitane[32];
  byte c = 150;

//  tft.fillRect(0, 0, 320, 480, 0);
  for(int i = 0; i<5; i++) {
    citaj(precitane);
    snprintf(bafer, 32, texty[i], precitane);
    printmsg(i*20, bafer);
  }
}

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
