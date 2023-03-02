#ifndef LIB_NEO_PIXEL
#define LIB_NEO_PIXEL

#include <Adafruit_NeoPixel.h>

#define PIN_RGB_lED 27

class Lib_Neopixel
{
private:
    /* data */
    Adafruit_NeoPixel pixels = Adafruit_NeoPixel(1, PIN_RGB_lED, NEO_GRB + NEO_KHZ800);
public:
    Lib_Neopixel(/* args */);
    //~Lib_Neopixel();

    void begin();
    void setUp();
    void setBright(uint8_t brightNess);
    void showPixel(uint8_t pinLed, uint8_t pRed, uint8_t pGreen, uint8_t pBlue);
};

// Lib_Neopixel::Lib_Neopixel(/* args */)
// {
// }

// Lib_Neopixel::~Lib_Neopixel()
// {
// }


#endif