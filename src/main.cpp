#ifndef PIO_UNIT_TESTING
#include <Arduino.h>
#include "app/EventLogger.h"
#include "hardware/Rtc.h"
#include "hardware/CsvStorage.h"

Rtc rtc(Wire);
CsvStorage storage("data");

void setup() {
    Wire.begin();
    bool rtcOk = rtc.begin();
    bool sdOk = storage.begin();

    EventLogger::init("log.txt", rtcOk ? &rtc : nullptr);

    if (!rtcOk) EventLogger::write("rtc: DS3231 not found");
    if (!sdOk) EventLogger::write("storage: SD card not found");
    EventLogger::write("node started");
}

void loop() {
    if (Serial.available()) {
        String line = Serial.readStringUntil('\n');
        line.trim();
        if (line.startsWith("T")) {
            time_t t = line.substring(1).toInt();
            rtc.setTime(t);
            EventLogger::write("rtc: time set");
        } else if (line == "N") {
            Serial.println((unsigned long)rtc.now());
        }
    }
}
#endif
