#include "DataLogger.h"
#include "EventLogger.h"

bool DataLogger::sample() {
    std::optional<float> p = sensor.read();
    if (!p) {
        EventLogger::write("datalogger: sensor read failed");
        return false;
    }

    time_t t = clock.now();
    if (!storage.write(t, *p)) {
        EventLogger::write("datalogger: storage write failed");
        return false;
    }
    return true;
}