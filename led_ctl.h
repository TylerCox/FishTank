#ifndef LED_CTL_H
#define LED_CTL_H

#define BRIGHTNESS  200
#define MS_PER_UPDATE 1000
#define MS_PER_LED_MOVE 200

void led_setup();
void led_loop();

class LED_CTL{
  public:
    LED_CTL(){};
    void led_setup();
    void led_loop(unsigned int ms);
    void updateTime(int hour, int minute);
    void setMaxBrightness(unsigned int val);
    void setUpdateMSPeriod(unsigned int ms){updateMS_ = ms;}
    void setSpeedMSPeriod(unsigned int ms){speedMS_ = ms;}
  private:
    unsigned int lastUpdate_=0;
    unsigned int lastLedMove_=0;
    int lastMinute_ = 0;
    int lastHour_ = 0;
    uint8_t brightness_ = 0;
    uint8_t brightnessMax_ = BRIGHTNESS;
    unsigned int updateMS_ = MS_PER_UPDATE;
    unsigned int speedMS_ = MS_PER_LED_MOVE;

    int linear(int pos, int st, int nd, int x1, int x2);
    int protectedLinear(int pos, int st, int nd, int x1, int x2);
    
    uint8_t calculateLight(int hour, int minute);
    void FillLEDsFromPaletteColors(uint8_t colorIndex);
    void SetupTotallyRandomPalette();
    void SetupBlackAndWhiteStripedPalette();
    void SetupPurpleAndGreenPalette();
};

#endif
