#pragma once

/** @brief Module that logs error and event messages */
namespace EventLogger {
    /**
     * @brief Initialises the logger and sets the output path.
     * @param path log file on the SD card.
     * @return false if the log could not be opened.
     */
    bool init(const char* path);
    void write(const char* msg);
}