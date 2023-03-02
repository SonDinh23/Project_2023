#include <Lib_ProjectSmart.h>

Lib_ProjectSmart::Lib_ProjectSmart() {

}

void Lib_ProjectSmart::begin() {
    oled.begin();
}

void Lib_ProjectSmart::beginRTC() {
    rtc.begin();
    if (!rtc.isrunning()) {
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
        //rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
    }
}

void Lib_ProjectSmart::beginMAX30102() {
    // Initialize sensor
    if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) //Use default I2C port, 400kHz speed
    {
        Serial.println("MAX30105 was not found. Please check wiring/power. ");
        while (1);
    }
    Serial.println("Place your index finger on the sensor with steady pressure.");
}

void Lib_ProjectSmart::setUpMAX30102() {
    particleSensor.setup(); //Configure sensor with default settings
    particleSensor.setPulseAmplitudeRed(0x0A); //Turn Red LED to low to indicate sensor is running
    particleSensor.setPulseAmplitudeGreen(0); //Turn off Green LED
}

void Lib_ProjectSmart::checkTemperature(long valueIr) {
    static long lastValueIr = 0;
    if(valueIr != lastValueIr) {
        oled.printTemperature(1, 30, 37, lastValueIr, valueIr);
        lastValueIr = valueIr;
    }
}

void Lib_ProjectSmart::checkValueHR(int avgBPM) {
    static int lastAvgBPM = 0;
    if(avgBPM != lastAvgBPM) {
        oled.printHeatRate(1, 30, 60, lastAvgBPM, avgBPM);
        lastAvgBPM = avgBPM;
    }
}

void Lib_ProjectSmart::checkRTC(uint8_t month, uint8_t day, uint8_t hour, uint8_t minutes) {
    static uint8_t lastMonth = 0;
    static uint8_t lastDay = 0;
    static uint8_t lastHour = 0;
    static uint8_t lastMinutes = 0;

    if(month != lastMonth) {
        oled.printRTC(1, 30, 37, lastMonth, month);
        lastMonth = month;
    }
    if(day != lastDay) {
        oled.printRTC(1, 50, 37, lastDay, day);
        lastDay = day;
    }
    if(hour != lastHour) {
        oled.printRTC(1, 70, 37, lastHour, hour);
        lastHour = hour;
    }
    if(minutes != lastMinutes) {
        oled.printRTC(1, 90, 37, lastMinutes, minutes);
        lastMinutes = minutes;
    }
}

void Lib_ProjectSmart::valueHeartRate() {
    //for(;;) {
         irValue = particleSensor.getIR();

        if (checkForBeat(irValue) == true)
        {
            //We sensed a beat!
            long delta = millis() - lastBeat;
            lastBeat = millis();

            beatsPerMinute = 60 / (delta / 1000.0);

            if (beatsPerMinute < 255 && beatsPerMinute > 20)
            {
                rates[rateSpot++] = (byte)beatsPerMinute; //Store this reading in the array
                rateSpot %= RATE_SIZE; //Wrap variable

            //Take average of readings
                beatAvg = 0;
                for (byte x = 0 ; x < RATE_SIZE ; x++)
                    beatAvg += rates[x];
                beatAvg /= RATE_SIZE;
            }
        }

        Serial.print("IR=");
        Serial.print(irValue);
        Serial.print(", BPM=");
        Serial.print(beatsPerMinute);
        Serial.print(", Avg BPM=");
        Serial.print(beatAvg);

        checkValueHR(beatAvg);
        

        Serial.println();
    //}
    
   
}

void Lib_ProjectSmart::valueRTC() {
    DateTime now = rtc.now();
    now = rtc.now();
    checkRTC(now.month(), now.day(), now.hour(), now.minute());
    Serial.print(now.month());
    Serial.print("\t");
    Serial.print(now.day());
    Serial.print("\t");
    Serial.print(now.hour());
    Serial.print("\t");
    Serial.print(now.minute());
    Serial.print("\t");
}