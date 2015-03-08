/*
* This is a minimal example, see extra-examples.cpp for a version
* with more explantory documentation, example routines, how to
* hook up your pixels and all of the pixel types that are supported.
*
*/
#include "application.h"
//#include "spark_disable_wlan.h" // For faster local debugging only
#include "neopixel.h"
// IMPORTANT: Set pixel COUNT, PIN and TYPE
#define PIXEL_PIN A1
#define PIXEL_COUNT 132
#define PIXEL_TYPE WS2812B

#define R1 13
#define R2 18
#define R3 20

#define MR 15
#define ML 15

#define L1 20
#define L2 18
#define L3 13

int color1;
int color2;
int color3;
int color4;
int times;

int point[7];

int test(String cmd);
int goRight(String cmd);
int goLeft(String cmd);
int goReg(String cmd);
int goStop(String cmd);

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);
void setup()
{
strip.begin();
strip.setBrightness(50);
strip.show(); // Initialize all pixels to 'off'
Spark.function("tests", test);
Spark.function("rights", goRight);
Spark.function("lefts", goLeft);
Spark.function("regs", goReg);
Spark.function("stops", goStop);
Spark.variable("color1", &color1, INT);
color1=4;
times=10;
}

int test(String cmd){
    return 159; 
}

int goRight(String cmd){
    refresh();
    right(times);
    return 0; 
}

int goLeft(String cmd){
    refresh();
    left(times);
    return 1; 
}

int goReg(String cmd){
    refresh();
    reg(times);
    return 2; 
}

int goStop(String cmd){
    refresh();
    stop(times);
    return 3; 
}

void points(int start, int count){
    point[0]=start;
    point[1]=start+(count*1/6);
    point[2]=start+(count*2/6);
    point[3]=start+(count*3/6);
    point[4]=start+(count*4/6);
    point[5]=start+(count*5/6);
    point[6]=start+(count*6/6);
}
void loop()
{
rainbow(times);
//right(time);
//stop(time);
//left(time);
//reg(time);
}
void refresh(){
    uint16_t i;
    for(i=0; i<strip.numPixels(); i++) {
        strip.setPixelColor(i, 0);
    }
    strip.show();
}
void rainbow(uint8_t wait) {
uint16_t i, j;
for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
        strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
    }
    for(i=0; i<strip.numPixels(); i++) {
        strip.setPixelColor(i, 0);
    }
    strip.show();
    delay(wait);
}
// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
if(WheelPos < 85) {
color1 = strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
return color1;
} else if(WheelPos < 170) {
WheelPos -= 85;
} else {
return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
WheelPos -= 170;
return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
}
}
void left(uint8_t wait){
    uint16_t j, k, l;
    j=0;
    k=128;
    l=0;
    
    strip.setPixelColor(91, j, k, l);
    strip.setPixelColor(110, j, k, l);
    strip.setPixelColor(125, j, k, l);
    
    strip.show();
    delay(wait);
    
    strip.setPixelColor(91, j, 0, l);
    strip.setPixelColor(110, j, 0, l);
    strip.setPixelColor(125, j, 0, l);
    
    strip.show();
    delay(wait);
    
    strip.setPixelColor(96, j, k, l);
    strip.setPixelColor(86, j, k, l);
    strip.setPixelColor(107, j, k, l);
    strip.setPixelColor(113, j, k, l);
    strip.setPixelColor(125, j, k, l);
    
    strip.show();
    delay(wait);
    
    strip.setPixelColor(96, j, 0, l);
    strip.setPixelColor(86, j, 0, l);
    strip.setPixelColor(107, j, 0, l);
    strip.setPixelColor(113, j, 0, l);
    strip.setPixelColor(125, j, 0, l);
    
    strip.show();
    delay(wait);
    
    strip.setPixelColor(100, j, k, l);
    strip.setPixelColor(81, j, k, l);
    strip.setPixelColor(105, j, k, l);
    strip.setPixelColor(114, j, k, l);
    strip.setPixelColor(125, j, k, l);
    
    strip.show();
    delay(wait);
    
    strip.setPixelColor(100, j, 0, l);
    strip.setPixelColor(81, j, 0, l);
    strip.setPixelColor(105, j, 0, l);
    strip.setPixelColor(114, j, 0, l);
    strip.setPixelColor(125, j, 0, l);
    
    strip.show();
    delay(wait);
}
int right(uint8_t wait){
    uint16_t j; j=0;
    uint16_t k; k=128;
    uint16_t l; l=0;
    
    strip.setPixelColor(6, j, k, l);
    strip.setPixelColor(41, j, k, l);
    strip.setPixelColor(22, j, k, l);
    
    points(0,R1);
    color1=point[0];
    
    strip.show();
    delay(wait);
    
    strip.setPixelColor(41, 0, 0, 0);
    strip.setPixelColor(22, 0, 0, 0);
    
    points(0,(R1+R2));
    color1=point[0];
    
    strip.show();
    delay(wait);
    
    strip.setPixelColor(45, j, k, l);
    strip.setPixelColor(35, j, k, l);
    strip.setPixelColor(20, j, k, l);
    strip.setPixelColor(24, j, k, l);
    strip.setPixelColor(6, j, k, l);
    
    points(0,(R1+R2+R3));
    color1=point[0];
    
    strip.show();
    delay(wait);
    
    strip.setPixelColor(45, 0, 0, 0);
    strip.setPixelColor(35, 0, 0, 0);
    strip.setPixelColor(20, 0, 0, 0);
    strip.setPixelColor(24, 0, 0, 0);
    
    points(0,(R1+R2+R3+MR));
    color1=point[0];
    
    strip.show();
    delay(wait);
    
    strip.setPixelColor(50, j, k, l);
    strip.setPixelColor(31, j, k, l);
    strip.setPixelColor(17, j, k, l);
    strip.setPixelColor(26, j, k, l);
    strip.setPixelColor(6, j, k, l);
    
    points(0,(R1+R2+R3+MR+ML));
    color1=point[0];
    
    strip.show();
    delay(wait);
    
    strip.setPixelColor(50, 0, 0, 0);
    strip.setPixelColor(31, 0, 0, 0);
    strip.setPixelColor(17, 0, 0, 0);
    strip.setPixelColor(26, 0, 0, 0);
    strip.setPixelColor(6, 0, 0, 0);
    
    points(0,(R1+R2+R3+MR+ML+L1));
    color1=point[0];
    
    strip.show();
    delay(wait);
    
    return color1;
}
void r(uint8_t wait){
    uint16_t j; j=0;
    uint16_t k; k=128;
    uint16_t l; l=0;
    
    points(0,R1);
    strip.setPixelColor(point[3], j, k, l);
    
    points(0+R1,R2);
    strip.setPixelColor(point[3], j, k, l);
    
    points(0+R1+R2,R3);
    strip.setPixelColor(point[3], j, k, l);
    
    strip.show();
    delay(wait);
    
    points(0+R1,R2);
    strip.setPixelColor(point[3], j, 0, l);
    
    points(0+R1+R2,R3);
    strip.setPixelColor(point[3], j, 0, l);
    
    strip.show();
    delay(wait);
    
    points(0,R1);
    strip.setPixelColor(point[3], j, k, l);
    
    points(0+R1,R2);
    strip.setPixelColor(point[2], j, k, l);
    strip.setPixelColor(point[4], j, k, l);
    
    points(0+R1+R2,R3);
    strip.setPixelColor(point[5], j, k, l);
    strip.setPixelColor(point[1], j, k, l);
    
    strip.show();
    delay(wait);
    
    points(0,R1);
    strip.setPixelColor(point[3], j, 0, l);
    
    points(0+R1,R2);
    strip.setPixelColor(point[2], j, 0, l);
    strip.setPixelColor(point[4], j, 0, l);
    
    points(0+R1+R2,R3);
    strip.setPixelColor(point[5], j, 0, l);
    strip.setPixelColor(point[1], j, 0, l);
    
    strip.show();
    delay(wait);
    
    points(0,R1);
    strip.setPixelColor(point[3], j, k, l);
    
    points(0+R1,R2);
    strip.setPixelColor(point[5], j, k, l);
    strip.setPixelColor(point[1], j, k, l);
    
    points(0+R1+R2,R3);
    strip.setPixelColor(point[6], j, k, l);
    strip.setPixelColor(point[0], j, k, l);
    
    strip.show();
    delay(wait);
    
    points(0,R1);
    strip.setPixelColor(point[3], j, 0, l);
    
    points(0+R1,R2);
    strip.setPixelColor(point[5], j, 0, l);
    strip.setPixelColor(point[1], j, 0, l);
    
    points(0+R1+R2,R3);
    strip.setPixelColor(point[6], j, 0, l);
    strip.setPixelColor(point[0], j, 0, l);
    
    strip.show();
    delay(wait);
}
void stop(uint8_t wait){
    uint16_t j;
    j=255;
    
    strip.setPixelColor(51, j, 0, 0);
    strip.setPixelColor(80, j, 0, 0);
    
    strip.show();
    delay(wait);
    
    strip.setPixelColor(55, j, 0, 0);
    strip.setPixelColor(78, j, 0, 0);
    
    strip.show();
    delay(wait);
    
    strip.setPixelColor(59, j, 0, 0);
    strip.setPixelColor(76, j, 0, 0);
    
    strip.show();
    delay(wait);
    
    strip.setPixelColor(62, j, 0, 0);
    strip.setPixelColor(73, j, 0, 0);
    
    strip.show();
    delay(wait);
    
    strip.setPixelColor(66, j, 0, 0);
    strip.setPixelColor(65, j, 0, 0);
    
    strip.show();
    delay(wait);
    
    strip.setPixelColor(51, 0, 0, 0);
    strip.setPixelColor(80, 0, 0, 0);
    strip.setPixelColor(55, 0, 0, 0);
    strip.setPixelColor(78, 0, 0, 0);
    strip.setPixelColor(59, 0, 0, 0);
    strip.setPixelColor(76, 0, 0, 0);
    strip.setPixelColor(62, 0, 0, 0);
    strip.setPixelColor(73, 0, 0, 0);
    strip.setPixelColor(66, 0, 0, 0);
    strip.setPixelColor(65, 0, 0, 0);
    
    strip.show();
    delay(wait);
}
void reg(uint8_t wait){
    uint16_t j;
    j=255;
    
    strip.setPixelColor(59, j, 0, 0);
    strip.setPixelColor(76, j, 0, 0);
    strip.setPixelColor(62, j, 0, 0);
    strip.setPixelColor(73, j, 0, 0);
    
    strip.show();
    delay(wait);
    
    strip.setPixelColor(59, 0, 0, 0);
    strip.setPixelColor(76, 0, 0, 0);
    strip.setPixelColor(62, 0, 0, 0);
    strip.setPixelColor(73, 0, 0, 0);
    
    strip.show();
    delay(wait);
}
