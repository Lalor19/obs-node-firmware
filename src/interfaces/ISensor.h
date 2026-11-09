#pragma once
#include <optional>

/** @brief Interface for sensors that can be sampled. */

class ISensor {
public:
    virtual ~ISensor() = default;       // Destructor.

    /**
     * @brief Reads one value from the sensor.
     * @return The reading, or empty if the read failed.
     */
    virtual std::optional<float> read() = 0;
};