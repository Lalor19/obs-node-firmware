#include "CsvStorage.h"
#include <SPI.h>
#include <string.h>
#include <stdlib.h>

namespace {
    const time_t SECONDS_PER_DAY = 86400;

    void buildPath(char* buf, size_t len, const char* dir, time_t t) {
        char date[9];
        strftime(date, sizeof(date), "%Y%m%d", gmtime(&t));
        snprintf(buf, len, "%s/%s.csv", dir, date);
    }
}

CsvStorage::CsvStorage(const char* dir) {
    strncpy(this->dir, dir, sizeof(this->dir) - 1);
    this->dir[sizeof(this->dir) - 1] = '\0';
}

bool CsvStorage::begin() {
    // SDIO mode
    if(!SD.begin(PIN_SD_CLK, PIN_SD_CMD_MOSI, PIN_SD_DAT0_MISO)) {
        return false;
    }
    if (!SD.exists(dir)) {
        SD.mkdir(dir);
    }
    return true;
}

bool CsvStorage::write(time_t t, float p) {
    int day = t / SECONDS_PER_DAY;
    
    // New day - close yesterday's file and open today's 
    if (day != current_day) {
        if (file) {
            file.close();
        }
        char path[32];
        buildPath(path, sizeof(path), dir, t);
        file = SD.open(path, FILE_WRITE);
        if (!file) {
            current_day = -1;
            return false;
        }
        current_day = day;
    }
    char timestamp[20];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", gmtime(&t));

    file.print((long long)t);
    file.print(',');
    file.print(timestamp);
    file.print(',');
    file.println(p, 4);
    file.flush();
    return true;
}

int CsvStorage::read(time_t from, time_t to, int step, float* out, int max) {
    if (step < 1) {
        step = 1;
    }
    int count = 0;
    int index = 0;

    for (time_t day = from / SECONDS_PER_DAY; day <= to / SECONDS_PER_DAY && count < max; day++) {
        char path[32];
        buildPath(path, sizeof(path), dir, day * SECONDS_PER_DAY);
        File f = SD.open(path, FILE_READ);
        if (!f) {
            continue;
        }

        while (f.available() && count < max) {
            String line = f.readStringUntil('\n');

            // Column 1: unix time
            char* end;
            time_t t = strtoll(line.c_str(), &end, 10);
            if (*end != ',') {
                continue;
            }

            // Column 2: readabe date
            char* second = strchr(end + 1, ',');
            if (!second) {
                continue;
            }

            // Column 3: pressure
            float p = strtof(second + 1, nullptr);
            
            if (t < from || t > to) {
                continue;
            }
            if (index % step == 0) {
                out[count++] = p;
            }
            index++;
        }
        f.close();
    }
    return count;
}