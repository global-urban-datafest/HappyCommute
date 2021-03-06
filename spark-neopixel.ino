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
#define PIXEL_COUNT 8
#define PIXEL_TYPE WS2812B

#define R1[450] {0, 1}
#define R2[450] {0, 1}
#define R3[450] {0, 1}

#define MR[450] {0, 1}
#define ML[450] {0, 1}

#define L1[450] {0, 1}
#define L2[450] {0, 1}
#define L3[450] {0, 1}

int color1;
int color2;
int color3;
int color4;


Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);
void setup()
{
strip.begin();
strip.show(); // Initialize all pixels to 'off'
Spark.variable("color1", &color1, INT);
Spark.variable("color2", &color2, INT);
Spark.variable("color3", &color3, INT);
Spark.variable("color4", &color4, INT);
Spark.function("right", right);
Spark.function("left", left);
Spark.function("reg", reg);
Spark.function("stop", stop);
}
void loop()
{
strip.setBrightness(100);
rainbow(20);
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
}
// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
if(WheelPos < 85) {
color1=strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
return color1;
} else if(WheelPos < 170) {
WheelPos -= 85;
color2= strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
return color2;
} else {
WheelPos -= 170;
color3=strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
return color3;
}
}
void left(){
color1=strip.Color(0, 0, 255);
strip.setPixelColor(0, color1 & 255);
strip.show();
delay(wait);
delay(1000);
}
void right(){
color2=strip.Color(0, 255, 0);
strip.setPixelColor(0, color2 & 255);
strip.show();
delay(wait);
delay(1000);
}
void reg(){
color3=strip.Color(255, 0, 0);
strip.setPixelColor(0, color3 & 255);
strip.show();
delay(wait);
delay(1000);
}
void stop(){
color4=strip.Color(255, 255, 255);
strip.setPixelColor(0, color4 & 255);
strip.show();
delay(wait);
delay(1000);
}