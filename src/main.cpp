#ifndef PIO_UNIT_TESTING
#include <Arduino.h>
#include "app/EventLogger.h"

void setup() {
    EventLogger::init("log.txt");
    delay(5000);
    EventLogger::write("Hello from the feather");
}

void loop() {}
#endif
