#ifndef LED_CTL_H
#define LED_CTL_H

#define BRIGHTNESS  180

void led_setup();
void led_loop();

class LED_CTL{
  public:
    LED_CTL(){};
    void led_setup();
    void led_loop(unsigned int ms);
    void updateTime(int hour, int minute);
    void setMaxBrightness(unsigned int val);
  private:
    unsigned int lastUpdate_=0;
    int lastMinute_ = 0;
    int lastHour_ = 0;
    uint8_t brightness_ = 0;
    uint8_t brightnessMax_ = BRIGHTNESS;

    int linear(int pos, int st, int nd, int x1, int x2);
    int protectedLinear(int pos, int st, int nd, int x1, int x2);
    
    uint8_t calculateLight(int hour, int minute);
    void FillLEDsFromPaletteColors(uint8_t colorIndex);
    void SetupTotallyRandomPalette();
    void SetupBlackAndWhiteStripedPalette();
    void SetupPurpleAndGreenPalette();
};

#endif
