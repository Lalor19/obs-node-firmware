#include "Rtc.h"

bool Rtc::begin() {
    return rtc.begin(&wire);
}

bool Rtc::setTime(time_t t) {
    rtc.adjust(DateTime(t));
    return true;
}

time_t Rtc::now() {
    return rtc.now().unixtime();
}