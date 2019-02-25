#include <FastLED.h>
#include <math.h>
#include "led_ctl.h"
#include "Shared.h"


#define NUM_LEDS    106
#define BRIGHTNESS  255
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 100

// This example shows several ways to set up and use 'palettes' of colors
// with FastLED.
//
// These compact palettes provide an easy way to re-colorize your
// animation on the fly, quickly, easily, and with low overhead.
//
// USING palettes is MUCH simpler in practice than in theory, so first just
// run this sketch, and watch the pretty lights as you then read through
// the code.  Although this sketch has eight (or more) different color schemes,
// the entire sketch compiles down to about 6.5K on AVR.
//
// FastLED provides a few pre-configured color palettes, and makes it
// extremely easy to make up your own color schemes with palettes.
//
// Some notes on the more abstract 'theory and practice' of
// FastLED compact palettes are at the bottom of this file.

/*
 * Pre-def pallets
 * CloudColors_p
 * LavaColors_p
 * OceanColors_p
 * ForestColors_p
 * HeatColors_p
 */

CRGBPalette16 currentPalette;
TBlendType    currentBlending;

extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;

void LED_CTL::led_setup() {
    delay( 3000 ); // power-up safety delay
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(  BRIGHTNESS );
    
    currentPalette = CloudColors_p;
    currentBlending = LINEARBLEND;
}


void LED_CTL::led_loop(unsigned int ms)
{
    if(ms - this->lastUpdate >= UPDATES_PER_SECOND){
      this->lastUpdate = ms;
      
      static uint8_t startIndex = 0;
      startIndex = startIndex + 1; /* motion speed */
      
      FillLEDsFromPaletteColors( startIndex);
      
      FastLED.show();
    }
}

void LED_CTL::FillLEDsFromPaletteColors( uint8_t colorIndex)
{    
    for( int i = 0; i < NUM_LEDS; i++) {
        leds[i] = ColorFromPalette( currentPalette, colorIndex, brightnessMax, currentBlending);
        colorIndex += 3;
    }
}

uint8_t LED_CTL::calculateLight(int hour, int minute){
  //1440 minutes in a day.
  //https://www.desmos.com/calculator/yifocw4p2u
  double pos = 2*(double(((hour*60)+minute))/1440);
  pos = sin(M_PI*(pos+1)); //Offset +1;
  pos += 0.8;
  pos /= 1.5;
  //Trim top and bottom.
  if(pos>1){
    pos=1;
  }
  if(pos<0){
    pos=0;
  }
  return BRIGHTNESS*pos;
}

void LED_CTL::updateTime(int hour, int minute){ 
  if(minute != lastMinute || hour != lastHour){
    brightnessMax = calculateLight(hour,minute);
    lastMinute = minute;
    lastHour = hour;
    
    currentPalette = LavaColors_p;
    #if 0
    switch(hour){
      case 1:
      case 2:
      case 3:
      case 4:
      case 5:
        currentPalette = ForestColors_p;
        break;
      case 6:
        currentPalette = LavaColors_p;
        break;
      case 7:
      case 8:
      case 9:
      case 10:
      case 11:
      case 12:
      case 13:
      case 14:
      case 15:
      case 16:
      case 17:
      case 18:
        currentPalette = CloudColors_p;
        break;
      case 19:
      case 20:
      case 21:
      case 22:
      case 23:
      case 0:
        currentPalette = OceanColors_p;
        break;
    } 
    #endif
  }
}

