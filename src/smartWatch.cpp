#include <Arduino.h>
#include <freertos/FreeRTOS.h>

#include "Lib_ProjectSmart.h"
#include "LibWifi_FireBase.h"
#include "Lib_Neopixel.h"
#include "LibOled.h"

#define touchPin 4
#define Threshold 40
RTC_DATA_ATTR int8_t stateSleep = 0;

// WIFI_SSID = "BO DAM CHO"
// WIFI_PASSWORD = "0902kochoddau795hoilamgif5570mowddi"

// WIFI_SSID = "Vulcan Augmetics"
// WIFI_PASSWORD = "wearevulcan.com"

const char *WIFI_SSID = "BO DAM CHO";
const char *WIFI_PASSWORD = "0902kochoddau795hoilamgif5570mowddi";

#define FIREBASE_HOST "smartwatch-4e534-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "h6997DRmUwSgFzGiF5GV5XxOnbtsxlXIaQXNaP1E"

int statett = 0;
int stateSS = 0;
uint32_t lastTime = millis();
uint32_t lastTimeA = millis();
uint32_t lastTimeB = millis();
uint32_t lastTimeC = millis();

TaskHandle_t task_data;
TaskHandle_t task_measure;
TaskHandle_t task_sleep;

LibWifi_FireBase libwifi_fireBase;
Lib_Neopixel libneopixel;
LibOled liboled;
Lib_ProjectSmart libpro;

void callBack() {}

void Task_Data(void *Parameters)
{
  for (;;)
  {
    if (millis() - lastTimeA > 1000)
    {
      Serial.println("Gửi");
      libwifi_fireBase.sendIntdata("/Smart Watch/heart raze", libpro.beatAvg);
      if(libpro.irValue > 50000) {
        libwifi_fireBase.sendIntdata("/Smart Watch/heart raze valid", 1);
      }else {
        libwifi_fireBase.sendIntdata("/Smart Watch/heart raze valid", 0);
      }    
      lastTimeA = millis();
    }
    vTaskDelay(100);
  }
}

void Task_Measure(void *Parameters)
{
  libneopixel.showPixel(0, 0 , 0, 150);
  for (;;)
  {
    if(millis() - lastTimeB > 1000) {
      libpro.valueRTC();
      lastTimeB = millis();
    }
    libpro.valueHeartRate();

    if(libpro.irValue < 50000) {
      if(millis() - lastTimeC > 200) {
        stateSS++;
        lastTimeC = millis();
      }
      if(stateSS >= 3) {
        libneopixel.showPixel(0, 0 , 0, 0);
        touchAttachInterrupt(T0, callBack, Threshold);
        esp_sleep_enable_touchpad_wakeup();
        
        Serial.println("Going to sleep now");
        statett = 0;
        liboled.deleteDisplay();
        vTaskDelay(300);
        esp_deep_sleep_start();
        Serial.println("This will never be printed");
      }
    }else {
      stateSS = 0;
    }
    vTaskDelay(1);
  }
}

void Task_Sleep(void *Parameters)
{
  for (;;)
  {
    //Serial.println(touchRead(touchPin) );
    if(touchRead(touchPin) < 50) {
      //Serial.println("ok");
      if (millis() - lastTime > 1000)
      {
        statett++;
        libneopixel.showPixel(0,150,80,80);
        Serial.println(statett);
        lastTime = millis();
      }
      libneopixel.showPixel(0,0,0,0);
    } else if(touchRead(touchPin) > 50) {
      statett = 0;
      //libneopixel.showPixel(0, 0 , 0, 150);
    }
    
    if (statett >=3)
    {
      Serial.println("oke");
      touchAttachInterrupt(T0, callBack, Threshold);
      esp_sleep_enable_touchpad_wakeup();
      Serial.println("Going to sleep now");
      statett = 0;
      libneopixel.showPixel(0, 0 , 0, 0);
      liboled.deleteDisplay();
      vTaskDelay(300);
      esp_deep_sleep_start();
      Serial.println("This will never be printed");
      // xTaskCreatePinnedToCore(Task_Sleep1, "Task_Sleep1", 5000, NULL, 1, &task_sleep1, 0);
    }
    //Serial.println("ok");
    vTaskDelay(100);
  }
}

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);

  libwifi_fireBase.beginWiFi(WIFI_SSID, WIFI_PASSWORD);
  libwifi_fireBase.beginFB(FIREBASE_AUTH, FIREBASE_HOST);
  libneopixel.begin();
  liboled.begin();

  libneopixel.showPixel(0, 150 , 150, 150);
  
  liboled.intro();
  delay(1000);
  liboled.deleteDisplay();
  libwifi_fireBase.setupWiFi();
  liboled.deleteDisplay();
  libwifi_fireBase.setupFB();
  liboled.deleteDisplay();
  Serial.println("Ok");
  libneopixel.showPixel(0, 0 , 0, 0);

  libpro.begin();
  libpro.beginRTC();
  libpro.beginMAX30102();
  libpro.setUpMAX30102();

  touchAttachInterrupt(T0, callBack, Threshold);

  if (stateSleep == 0)
  {
    esp_sleep_enable_touchpad_wakeup();
    Serial.println("Going to sleep now");
    stateSleep = 1;
    esp_deep_sleep_start();
    Serial.println("This will never be printed");
  }

  xTaskCreatePinnedToCore(Task_Measure, "Task_Measure", 10000, NULL, 3, &task_measure, 1);
  xTaskCreatePinnedToCore(Task_Sleep, "Task_Sleep", 10000, NULL, 2, &task_sleep, 0);
  xTaskCreatePinnedToCore(Task_Data, "Task_Data", 10000, NULL, 1, &task_data, 0);
  
  vTaskStartScheduler();
}

void loop()
{
  // put your main code here, to run repeatedly:
  
  vTaskDelete(NULL);
  

}