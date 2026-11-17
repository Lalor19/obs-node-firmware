#pragma once
#include "interfaces/IRtc.h"

/** @brief Module that logs error and event messages */
namespace EventLogger {
    /**
     * @brief Initialises the logger and sets the output path.
     * @param path log file on the SD card.
     * @param rtc clock for timestamps, or nullptr to usetime since boot.
     * @return false if the log could not be opened.
     */
    bool init(const char* path, IRtc* rtc);
    void write(const char* msg);
}