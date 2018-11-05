#ifndef LED_CTL_H
#define LED_CTL_H

void led_setup();
void led_loop();

class LED_CTL{
  public:
    LED_CTL(){};
    void led_setup();
    void led_loop(unsigned int ms);
  private:
    unsigned int lastUpdate=0;
    void ChangePalettePeriodically();
    void FillLEDsFromPaletteColors(uint8_t colorIndex);
    void SetupTotallyRandomPalette();
    void SetupBlackAndWhiteStripedPalette();
    void SetupPurpleAndGreenPalette();
};

#endif
