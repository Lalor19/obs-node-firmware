#include <Arduino.h>
#include "EventLogger.h"

namespace EventLogger {
    bool init(const char* path) {
        Serial.begin(115200);
        return true;
    }
    void write(const char* msg) {
        Serial.println(msg);
    }
}