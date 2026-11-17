#pragma once
#include <optional>
#include "interfaces/ISensor.h"

/** @brief Sensor for tests that returns a value set by the test. */
class SensorDouble : public ISensor {
public:
    std::optional<float> value;    // Simulates a failed read.
    std::optional<float> read() override { return value; }
};