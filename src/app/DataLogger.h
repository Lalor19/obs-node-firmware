#pragma once
#include "interfaces/ISensor.h"
#include "interfaces/IRtc.h"
#include "interfaces/IStorage.h"

/** @brief takes timestamped sensor readings and stores them. */
class DataLogger {
public:
    DataLogger(ISensor& sensor, IRtc& clock, IStorage& storage) 
    : sensor(sensor), clock(clock), storage(storage) {}

    /** @brief Takes one reading and stores it. 
     * @return False if reading or storing failed. 
     */
    bool sample();

    private:
    ISensor& sensor;
    IRtc& clock;
    IStorage& storage;
};