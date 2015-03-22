#include "FastLED.h"
#include <SoftwareSerial.h>

#define DATA_PIN 6
#define NUM_COLORS 6

//--------------------------------------------------------------------------------------------------------------------
// I would suggest only playing with the settings in this section, and only if necessary.

// Duration between the updating of the LEDs
#define INTERVAL 25

// The might need to be changed I think there were 16 for both headphones
// it shouldn't matter if there are less than 16 actually connected though
#define NUM_LEDS 16

// Here's where you set the interval between color changes while in
// demo mode (in milliseconds). Make sure demoMode bool is also set true.
// If you wanna change the colors in the sequence, that can be done by
// changing the RGB values in demoColors
#define DEMO_INTERVAL 15000
const bool demoMode = false;
const int numDemoColors = 6;
const int demoColors[numDemoColors][3] = {{0,255,255},{255,102,153},{51,204,51},{255,204,0},{0,0,204},{153,51,255}};

// Step size to use for the transition between colors (smaller number gives higher resolution but also slower transitions)
int colorShiftAmount=2;
// Same deal as above but this handles the regular pulsing of the color
int fadeAmount = 2;
// 
//--------------------------------------------------------------------------------------------------------------------

SoftwareSerial mySerial(2, 3); // RX, TX

byte colors[NUM_COLORS];
int colors_index=0;
int currentRGB[3]={0,0,0};
int newRGB[3]={0,0,0};
bool differentColors[3]={false, false, false};
long nextUpdate = 0;
int dimmer = 200;
CRGB leds[NUM_LEDS];
long demoUpdate = 0;
int demoIndex=0;


void setup(){
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  Serial.begin(9600);
  mySerial.begin(9600);
}

void loop()
{
  if (mySerial.available()>0)
  {
    if (colors_index < NUM_COLORS)
    {
      // let's read only one byte
      char ch = (char)mySerial.read();
      if (ch != ';'){
        ch = (ch<='9') ? (ch-'0') : (ch-'A'+10) ;
        colors[colors_index] = (byte)ch;
        // if a byte has been read, increment the index
        if ((int)colors[colors_index] != -1)
            ++colors_index;
      }
      else
        colors_index = 0;
    }
  }
  if (Serial.available()>0)
  {
    if (colors_index < NUM_COLORS)
    {
      // let's read only one byte
      char ch = (char)Serial.read();
      if (ch != ';'){
        ch = (ch<='9') ? (ch-'0') : (ch-'A'+10) ;
        colors[colors_index] = (byte)ch;
        // if a byte has been read, increment the index
        if ((int)colors[colors_index] != -1)
            ++colors_index;
      }
      else
        colors_index = 0;
    }
  }
  if(colors_index >= NUM_COLORS){
    saveNewColor();
  }
  if(demoMode)
  {
    if(millis()>demoUpdate)
    {
      demoUpdate+=DEMO_INTERVAL;
      Serial.println();
      // reset the index to start over
      demoIndex++;
      if(demoIndex==numDemoColors)
        demoIndex=0;
      differentColors[0]=true;
      differentColors[1]=true;
      differentColors[2]=true;
      // set RGB for all LEDs
      // The received bytes need to be shifted together to form one actual byte
      // this is the final step in the conversion from ascii to hex
      for(int i = 0; i<3; i++)
      {
        newRGB[i]=demoColors[demoIndex][i];
        Serial.print(currentRGB[i], DEC);
        Serial.print(":");
        Serial.print(newRGB[i], DEC);
        Serial.print(" ");
      }
      Serial.println();
    }
  }
  if(millis() > nextUpdate)
  {
    updateColor();
  }
}

void saveNewColor()
{
  Serial.println();
  // reset the index to start over
  colors_index = 0;
  differentColors[0]=true;
  differentColors[1]=true;
  differentColors[2]=true;
  // set RGB for all LEDs
  // The received bytes need to be shifted together to form one actual byte
  // this is the final step in the conversion from ascii to hex
  for(int i = 0; i<3; i++)
  {
    newRGB[i]=(colors[i*2] | (colors[i*2+1] << 4));
    Serial.print(currentRGB[i], DEC);
    Serial.print(":");
    Serial.print(newRGB[i], DEC);
    Serial.print(" ");
  }
  Serial.println();
}

void updateColor()
{
  nextUpdate+=INTERVAL;
  for(int i = 0; i < NUM_LEDS; i++ )
  {
    leds[i].setRGB(currentRGB[0],currentRGB[1],currentRGB[2]);
    leds[i].fadeLightBy(dimmer);
  }
  FastLED.show();
  dimmer+=fadeAmount;
  if (dimmer == 240 || dimmer == 180)
    fadeAmount=-fadeAmount;
    
  if(differentColors[0] || differentColors[1] || differentColors[2])
  {
    for(int i=0; i<3; i++)
    {
      if(currentRGB[i]<newRGB[i])
      {
        currentRGB[i]+=colorShiftAmount;
        if (currentRGB[i]>=newRGB[i])
        {
          currentRGB[i]=newRGB[i];
        }
      }
      else if (currentRGB[i]>newRGB[i])
      {
        currentRGB[i]-=colorShiftAmount;
        if (currentRGB[i]<=newRGB[i])
        {
          currentRGB[i]=newRGB[i];
        }
      }
      else
        differentColors[i]=false;
    }
  }
}
