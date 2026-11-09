#pragma once
#include <time.h>

/** @brief Interface for a real-time clock providing the current time. */
class IRtc {
public:
    virtual ~IRtc() = default;      // Destructor.

    /** @brief Returns the current unix time (seconds since 1970-01-01) */
    virtual time_t now() = 0;
};