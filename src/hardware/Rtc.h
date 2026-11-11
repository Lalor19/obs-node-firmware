#pragma once
#include "interfaces/IRtc.h"
#include <Wire.h>
#include <RTClib.h>

/** @brief Real-time clock based on the DS3231*/
class Rtc : public IRtc{
public:
    explicit Rtc(TwoWire& wire) : wire(wire) {}

    /** @brief Initialises the clock. Returns false if the DS3231 is not found. */
    bool begin();

    /** @brief Sets the time, t is unix time (seconds since 1970-01-01, UTC). */
    bool setTime(time_t t);
    time_t now() override;

private:
    TwoWire& wire; 
    RTC_DS3231 rtc;
};