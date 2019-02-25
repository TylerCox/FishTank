#ifndef LED_CTL_H
#define LED_CTL_H

void led_setup();
void led_loop();

class LED_CTL{
  public:
    LED_CTL(){};
    void led_setup();
    void led_loop(unsigned int ms);
    void updateTime(int hour, int minute);
  private:
    unsigned int lastUpdate=0;
    int lastMinute = 0;
    int lastHour = 0;
    uint8_t brightnessMax=0;
    uint8_t calculateLight(int hour, int minute);
    void FillLEDsFromPaletteColors(uint8_t colorIndex);
    void SetupTotallyRandomPalette();
    void SetupBlackAndWhiteStripedPalette();
    void SetupPurpleAndGreenPalette();
};

#endif
