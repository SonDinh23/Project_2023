#ifndef LIB_WIFI_FIREBASE
#define LIB_WIFI_FIREBASE

#include <WiFi.h>
#include <FirebaseESP32.h>

#include "Lib_Neopixel.h"
#include "LibOled.h"

class LibWifi_FireBase
{
private:
    /* data */
    String path = "/";
    FirebaseData firebaseDate;
    LibOled screenOled;
    Lib_Neopixel leopixel;

public:
    LibWifi_FireBase();
    void beginWiFi(const char* WIFI_SSID, const char* WIFI_PASSWORD);
    void beginFB(String FIREBASE_AUTH,String FIREBASE_HOST);

    void setupWiFi();
    void setupFB();
    
    // send data to firebase
    void sendStrdata(String keyFB, String data);
    void sendIntdata(String keyFB, int data);
    void sendFloatdata(String keyFB, float data);

    // give data to firebase
    int32_t getIntdata(String keyFB);
    String getStrdata(String keyFB);
    float_t getFloatdata(String keyFB);
};

// LibWifi_FireBase::LibWifi_FireBase(/* args */)
// {
// }

#endif