#include <NTPClient.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <FastLED.h>
#include "Shared.h"
#include "led_ctl.h"


const char *ssid     = "SkyNet";
const char *password = "thec@k3isalie";

WiFiUDP ntpUDP;
// By default 'pool.ntp.org' is used with 60 seconds update interval and
// no offset
NTPClient timeClient(ntpUDP);
bool ntpStarted = false;

LED_CTL ledctl;






void checkNTP(){
  if(WiFi.status() == WL_CONNECTED){
    if(!ntpStarted){
      timeClient.begin();
      ntpStarted=true;
    }
    timeClient.update();
  }
}





void setup(){
  ledctl.led_setup();
  Serial.begin(115200);
  WiFi.begin(ssid, password);  
}

void loop(){
  checkNTP();
  
  Serial.println(timeClient.getFormattedTime());
  
  ledctl.led_loop(millis());

  //Using FastLED.delay() for the dithering.
  FastLED.delay(1);
} 

