#pragma once
#include "interfaces/IStorage.h"
#include <time.h>
#include <SD.h>
#include <SPI.h>

/** @brief Csv file storage on the feather's SD card */
class CsvStorage : public IStorage{
public:
    explicit CsvStorage(const char* dir);

    bool begin();

    bool write(time_t t, float p) override;

    int read(time_t from, time_t to, int step, float* out, int max) override;

private:
    File file;
    char dir [16];
    int current_day = -1;
};