#ifndef _SHARED_H
#define _SHARED_H

#define GREEN_LIGHT 5
#define AIR_CTRL 16
#define LED_PIN 23
#define STATUS_LED 2
#define CO2_CTRL 19
#define BUTTON_PIN 0

enum RUNNING_MODE
{
  mode_normal=0,
  mode_bright,
  mode_demo,
  MODE_COUNT,
};

RUNNING_MODE GetMode(void);

#endif
