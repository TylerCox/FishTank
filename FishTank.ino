#include <NTPClient.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <FastLED.h>
#include "Shared.h"
#include "led_ctl.h"


const char *ssid     = "SkyNet";
const char *password = "thec@k3isalie";
#define TIMEZONE_OFFSET_CST -21600 //6hours//November
#define TIMEZONE_OFFSET_CDT -18000 //5hours//March

bool wifiUp=false;

WiFiUDP ntpUDP;
// By default 'pool.ntp.org' is used with 60 seconds update interval and
// no offset
NTPClient timeClient(ntpUDP,TIMEZONE_OFFSET_CDT);
bool ntpStarted = false;

LED_CTL ledctl;

void eventTriggers(unsigned int hours, unsigned int minutes);

void checkNTP(){
  if(WiFi.status() == WL_CONNECTED){
    digitalWrite(STATUS_LED,1);
    wifiUp=true;
    if(!ntpStarted){
      timeClient.begin();
      ntpStarted=true;
    }
  }else{
    digitalWrite(STATUS_LED,0);
    wifiUp=false;
  }
  
  timeClient.update();
}

void setup(){
  pinMode(STATUS_LED,OUTPUT);
  pinMode(GREEN_LIGHT,OUTPUT);
  pinMode(AIR_CTRL,OUTPUT);
  pinMode(CO2_CTRL,OUTPUT);
  
  digitalWrite(STATUS_LED,HIGH);
  Serial.begin(115200);
  Serial.println("Start");
  
  ledctl.led_setup();
  
  WiFi.setHostname("FishTank");
  WiFi.begin(ssid, password);  
  
  digitalWrite(GREEN_LIGHT,HIGH);
  digitalWrite(AIR_CTRL,LOW );
  digitalWrite(STATUS_LED,LOW);
  digitalWrite(CO2_CTRL,LOW);
  delay( 1000 );
}

void loop(){
  static int ms=0;
  if(ms>=1000){
    checkNTP();
    eventTriggers(timeClient.getHours()%24,timeClient.getMinutes()%60);
    ledctl.updateTime(timeClient.getHours()%24,timeClient.getMinutes()%60);
    
    Serial.println(timeClient.getFormattedTime());
    ms=0;
  }
  ms++;

  ledctl.led_loop(millis());
  //Using FastLED.delay() for the dithering.
  FastLED.delay(1);
} 



void eventTriggers(unsigned int hours, unsigned int minutes){  
#if 1
  /*********************************************************
  GREEN LIGHT
  *********************************************************/
  if(hours>=8 && hours <24){
    digitalWrite(GREEN_LIGHT,HIGH);
  }else{
    digitalWrite(GREEN_LIGHT,LOW);
  }
  
  /*********************************************************
  AIR CONTROL
  *********************************************************/
  if(
    (hours>=10 && hours <23) 
      && minutes<30
  ){
    digitalWrite(AIR_CTRL,HIGH);
  }else{
    digitalWrite(AIR_CTRL,LOW);
  }

  /*********************************************************
  C02 CONTROL 
  Duty cycle 1/10, pressure built up in line will
  dissipate over the following 9 minutes. Keeps solenoid
  from getting hot.
  *********************************************************/
  if((hours>=8 && hours <22)
    && ((minutes%10)==0)
  ){
    //Using CO2 active high so if power goes out then CO2 stops.
    digitalWrite(CO2_CTRL,HIGH);
  }else{
    digitalWrite(CO2_CTRL,LOW);
  }
#endif
}

