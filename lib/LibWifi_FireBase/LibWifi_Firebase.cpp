#include "LibWifi_FireBase.h"

LibWifi_FireBase::LibWifi_FireBase() {}

void LibWifi_FireBase::beginWiFi(const char* WIFI_SSID, const char* WIFI_PASSWORD) {
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
}

void LibWifi_FireBase::beginFB(String FIREBASE_AUTH, String FIREBASE_HOST) {
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void LibWifi_FireBase::setupWiFi() {
    leopixel.begin();
    screenOled.begin();
    uint8_t x = 0;
    while(WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        x++;
        
        leopixel.showPixel(0, 150, 0 ,0);
        screenOled.connectingWifi();
        if(x == 10) {
            screenOled.deleteDisplay();
            break; 
        }
        delay(300);
    }
}

void LibWifi_FireBase::setupFB() {
    Firebase.reconnectWiFi(true);
    screenOled.deleteDisplay();
    leopixel.showPixel(0, 0, 150 ,0);
    screenOled.connectWifi();
    Serial.println("Connection");
    if(!Firebase.beginStream(firebaseDate, path)) {
        Serial.println("Reason: "+firebaseDate.errorReason());
        Serial.println();
    }
}

void LibWifi_FireBase::sendStrdata(String keyFB, String data) {
    Firebase.setString(firebaseDate, path + keyFB, data);
}

void LibWifi_FireBase::sendIntdata(String keyFB, int data) {
    Firebase.setInt(firebaseDate, path + keyFB, data);
}

void LibWifi_FireBase::sendFloatdata(String keyFB, float data) {
    Firebase.setFloat(firebaseDate, path + keyFB, data);
}

int32_t LibWifi_FireBase::getIntdata(String keyFB) {
    int32_t x;
    if(Firebase.getInt(firebaseDate, path + keyFB)) x = firebaseDate.intData();
    return x;
}

String LibWifi_FireBase::getStrdata(String keyFB) {
    String x;
    if(Firebase.getString(firebaseDate, path + keyFB)) x = firebaseDate.stringData();
    return x;
}

float_t LibWifi_FireBase::getFloatdata(String keyFB) {
    float_t x;
    if(Firebase.getFloat(firebaseDate, path + keyFB)) x = firebaseDate.floatData();
    return x;
}