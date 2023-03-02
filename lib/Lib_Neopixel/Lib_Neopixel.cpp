#include <Lib_Neopixel.h>

Lib_Neopixel::Lib_Neopixel() {

}

void Lib_Neopixel::begin() {
    pixels.begin();
}

void Lib_Neopixel::setUp() {

}

void Lib_Neopixel::setBright(uint8_t brightNess) {
    pixels.setBrightness(brightNess);
}

void Lib_Neopixel::showPixel(uint8_t pinLed, uint8_t pRed, uint8_t pGreen, uint8_t pBlue) {
    pixels.setPixelColor(pinLed, pixels.Color(pRed, pGreen, pBlue));
    pixels.show();
}