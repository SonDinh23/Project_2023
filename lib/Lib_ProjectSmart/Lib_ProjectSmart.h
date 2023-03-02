#ifndef LIB_PROJECT_SMART
#define LIB_PROJECT_SMART

#include "LibOled.h"
#include "Lib_Neopixel.h"

#include <Wire.h>
#include <MAX30105.h>
#include <heartRate.h>

#include <RTClib.h>

class Lib_ProjectSmart
{
private:
    /* data */
    LibOled oled;
    Lib_Neopixel pixel;

    MAX30105 particleSensor;

    RTC_DS1307 rtc;
    char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    

    const byte RATE_SIZE = 4; //Increase this for more averaging. 4 is good.
    byte rates[4]; //Array of heart rates
    byte rateSpot = 0;
    long lastBeat = 0; //Time at which the last beat occurred
public:

    long irValue;
    float beatsPerMinute;
    int beatAvg;

    Lib_ProjectSmart(/* args */);
    //~Lib_ProjectSmart();
    void begin();

    void beginRTC();

    void beginMAX30102();
    void setUpMAX30102();

    void checkValueHR(int avgBPM);
    void checkTemperature(long valueIr);
    void checkRTC(uint8_t month, uint8_t day, uint8_t hour, uint8_t minutes);

    void valueHeartRate();
    void valueRTC();

};

// Lib_ProjectSmart::Lib_ProjectSmart(/* args */)
// {
// }

// Lib_ProjectSmart::~Lib_ProjectSmart()
// {
// }



#endif