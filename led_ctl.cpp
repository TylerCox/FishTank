#include <FastLED.h>
#include <math.h>
#include "led_ctl.h"
#include "Shared.h"


#define NUM_LEDS    160
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

const CRGBPalette16 fall_color{
  0x5db3ad,
  0x9efff8,
  0xccba6a,
  0xffb8f4,
  
  0xb3a466,
  0xffb8f4,
  0xccba6a,
  0xb3a466,

  0x5db3ad,
  0xb3a466,
  0xffb8f4,
  0x9efff8,

  0xffb8f4,
  0x9efff8,
  0xccba6a,
  0xb3a466,
};

const CRGBPalette16 venom_color{
  0x8419b3,
  0xffc754,
  0xc43bff,
  0x1bcc7a,
  
  0x20b36f,
  0x1bcc7a,
  0xc43bff,
  0xffc754,
  
  0x8419b3,
  0x20b36f,
  0x1bcc7a,
  0xffc754,

  0x000000, //0xc43bff,
  0x000000, //0x8419b3,
  0x000000, //0x20b36f,
  0x000000, //0x8419b3,
  
};

void LED_CTL::led_setup() {
    delay( 3000 ); // power-up safety delay
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(  brightnessMax_ );
    
    currentPalette = CloudColors_p;
    currentBlending = LINEARBLEND;
}


void LED_CTL::led_loop(unsigned int ms)
{
    if(ms - this->lastUpdate_ >= UPDATES_PER_SECOND){
      this->lastUpdate_ = ms;
      
      static uint8_t startIndex = 0;
      startIndex = startIndex + 1; /* motion speed */
      
      FillLEDsFromPaletteColors( startIndex);
      
      FastLED.show();
    }
}

void LED_CTL::FillLEDsFromPaletteColors( uint8_t colorIndex)
{    
    for( int i = 0; i < NUM_LEDS; i++) {
        leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness_, currentBlending);
        colorIndex += 3;
    }
}

int LED_CTL::linear(int pos, int st, int nd, int x1, int x2){
  pos-=st;
  nd-=st;
  double t = pos;
  t/=nd;
  int rate = x2-x1;
  return (x1 + (rate*t));
}

int LED_CTL::protectedLinear(int pos, int st, int nd, int x1, int x2){
  int ret = linear(pos,st,nd,x1,x2);
  if(ret>brightnessMax_){
    return brightnessMax_;
  }
  if(ret<0){
    return 0;
  }
  return ret;
}

uint8_t LED_CTL::calculateLight(int hour, int minute){
  #if 0
  if(GetMode()==mode_demo){
    return brightnessMax_;
  }
    switch(hour){
      case 0:
      return protectedLinear(minute,
        0,60,
        ((brightnessMax_*2)/3),0);
      break;
      case 1:
      case 2:
      case 3:
      case 4:
      case 5:
      case 6:
      default:
      return 0;
      case 7:
      case 8:
      return protectedLinear((hour*60)+minute,
        (7*60),(9*60),
        0,brightnessMax_);
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
      case 19:
      case 20:
      case 21:
      case 22:
      return brightnessMax_;
      case 23:      
      return protectedLinear((hour*60)+minute,
        (23*60),(24*60),
        brightnessMax_,((brightnessMax_*2)/3));
    } 
    #else
    return brightnessMax_;
    #endif
}

void LED_CTL::updateTime(int hour, int minute){ 
  if(minute != lastMinute_ || hour != lastHour_){
    brightness_ = calculateLight(hour,minute);
    lastMinute_ = minute;
    lastHour_ = hour;
    
    #if 0
    switch(hour){
      default:
      case 3:
      case 4:
      case 5:
      case 6:
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
      case 19:
      case 20:
      case 21:
        currentPalette = fall_color;
        break;
      case 0:
      case 1:
      case 2:
      case 22:
      case 23:
        currentPalette = venom_color;
        break;
    } 
    #else
    currentPalette = venom_color;
    #endif
  }
}

void LED_CTL::setMaxBrightness(unsigned int val)
{
  if(val>=0 && val<=255)
  {
    brightnessMax_ = (uint8_t)val;
    lastMinute_ = 0;
    lastHour_ = 0;
  }
}

