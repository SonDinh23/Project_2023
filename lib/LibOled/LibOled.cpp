#include <LibOled.h>

LibOled::LibOled() {
    
}

void LibOled::begin() {
    delay(1);
    display.begin(i2c_address, true);
}

void LibOled::intro() {
    display.setCursor(80, 28);
    display.setTextSize(2);
    display.setTextColor(SH110X_WHITE);
    display.drawRoundRect(0, 0, 128, 64, 8, SH110X_WHITE);
    display.print("ECG");
    display.drawBitmap(20, 17, epd_bitmap_33, 50, 33, SH110X_WHITE);
    //display.drawBitmap(80, 5, heartRate_Live, 25, 21, SH110X_WHITE);
    //display.drawBitmap(80, 35, heartRate_Die, 25, 24, SH110X_WHITE);
    display.display();
}

void LibOled::deleteDisplay() {
    display.clearDisplay();
    display.display();
}

void LibOled::connectingWifi() {
    //display.setTextSize(2);
    display.setCursor(8, 28);
    display.setTextColor(SH110X_WHITE);
    display.drawRoundRect(0, 0, 128, 64, 8, SH110X_WHITE);
    display.print("Connecting...");
    display.drawBitmap(90, 23, epd_bitmap_1_preview_rev_1__1_, 25, 18, SH110X_WHITE);
    display.display();
    delay(150);
    display.drawBitmap(90, 23, epd_bitmap_1_preview_rev_1__1_, 25, 18, SH110X_BLACK);
    display.display();
}

void LibOled::connectWifi() {
    display.setCursor(20, 28);
    display.setTextColor(SH110X_WHITE);
    display.drawRoundRect(0, 0, 128, 64, 8, SH110X_WHITE);
    display.print("Connected");
    display.drawBitmap(85, 23, epd_bitmap_2__1_, 25, 20, 1);
    display.display();
    delay(100);
    
}

void LibOled::printRTC(uint8_t textSize,uint8_t x, uint8_t y, uint16_t lastValue, uint16_t newValue) {
    display.setTextSize(textSize);
    display.setCursor(x, y);
    display.setTextColor(SH110X_BLACK);
    display.print(lastValue);
    display.display();

    display.setCursor(x, y);
    display.setTextColor(SH110X_WHITE);
    display.print(newValue);
    display.display();
}

void LibOled::printTemperature(uint8_t textSize,uint8_t x, uint8_t y, uint16_t lastValue, uint16_t newValue) {
    display.setTextSize(textSize);
    display.setCursor(x, y);
    display.setTextColor(SH110X_BLACK);
    display.print(lastValue);
    display.display();

    display.setCursor(x, y);
    display.setTextColor(SH110X_WHITE);
    display.print(newValue);
    display.display();
}

void LibOled::printHeatRate(uint8_t textSize,uint8_t x, uint8_t y, uint16_t lastValue, uint16_t newValue) {
    display.setTextSize(textSize);
    display.setCursor(x, y);
    display.setTextColor(SH110X_BLACK);
    display.print(lastValue);
    display.display();

    display.setCursor(x, y);
    display.setTextColor(SH110X_WHITE);
    display.print(newValue);
    display.display();
}