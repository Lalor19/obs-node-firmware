#ifndef PIO_UNIT_TESTING
#include <Arduino.h>
#include "app/EventLogger.h"
#include "hardware/Rtc.h"

Rtc rtc(Wire);

void setup() {
    EventLogger::init("log.txt");
    Wire.begin();

    if (!rtc.begin()) {
        EventLogger::write("rtc: DS3231 not found");
    }
}

void loop() {
    if (Serial.available()) {
        String line = Serial.readStringUntil('\n');
        if (line.startsWith("T")) {
            time_t t = line.substring(1).toInt();
            rtc.setTime(t);
            Serial.println("rtc: time set");
            EventLogger::write("rtc: time set");
        } else if (line == "N") {
            Serial.println((unsigned long)rtc.now());
        }
    }
}
#endif
