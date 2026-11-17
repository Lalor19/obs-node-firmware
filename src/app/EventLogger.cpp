#include <Arduino.h>
#include "EventLogger.h"
#include <SD.h>
#include "interfaces/IRtc.h"

namespace EventLogger {

    namespace {
        File logFile;
        IRtc* clock = nullptr;
    }

    bool init(const char* path, IRtc* rtc) {
        clock = rtc;
        Serial.begin(115200);
        logFile = SD.open(path, FILE_WRITE);
        if (!logFile) {
            return false;
        }
        return true;
    }

    void write(const char* msg) {
        char line[128];

        if (clock != nullptr) {
            time_t t = clock->now();
            char timestamp[20];
            strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", gmtime(&t));
            snprintf(line, sizeof(line), "%s %s", timestamp, msg);
        } else {
            // In case of no rtc: use time since boot.
            snprintf(line, sizeof(line), "+%lums %s", millis(), msg);
        }

        if (logFile) {
            logFile.println(line);
            logFile.flush();
        }

        Serial.println(line);
    }
}