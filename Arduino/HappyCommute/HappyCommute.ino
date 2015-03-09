#include "FastLED.h"
#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // RX, TX

#define DATA_PIN 6
#define NUM_LEDS 3
#define NB_COLORS 9

byte colors[9];

CRGB leds[NUM_LEDS];

void setup(){
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  Serial.begin(9600);
  mySerial.begin(9600);
}

void loop() {
    static byte colors[NB_COLORS];
    static int colors_index=0;
    if (mySerial.available()>0){
      if (colors_index < NB_COLORS) {
          // let's read only one byte
          char ch = (char)mySerial.read();
          if (ch != ';'){
          ch = (ch<='9') ? (ch-'0') : (ch-'A'+10) ;
          colors[colors_index] = (byte)ch;
          // if a byte has been read, increment the index
          if ((int)colors[colors_index] != -1)
              ++colors_index;
          }
      }
    }
    if(colors_index >= NB_COLORS){
        // reset the index to start over
        colors_index = 0;
        // should'nt you iterate 3 by 3, i.e. having i=i+3 instead of i++ ?
        for(int i=0;i<NUM_LEDS ;i++){
          leds[i].red = (char)colors[i*3];
          leds[i].green = (char)colors[i*3+1];
          leds[i].blue = (char)colors[i*3+2];
          Serial.print(colors[i*3]);
          Serial.print(colors[i*3+1]);
          Serial.print(colors[i*3+2]);
        }
        FastLED.show();
        Serial.println();
    }
}
