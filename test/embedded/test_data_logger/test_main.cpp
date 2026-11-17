#include <Arduino.h>
#include <unity.h>
#include <SD.h>
#include <Wire.h>
#include "app/DataLogger.h"
#include "hardware/Rtc.h"
#include "hardware/CsvStorage.h"
#include "SensorDouble.h"
#include "app/EventLogger.h"

Rtc rtc(Wire);
CsvStorage storage("test");
SensorDouble sensor;
DataLogger logger(sensor, rtc, storage);

void test_sample_stores_reading() {
    sensor.value = 14.7341f;
    time_t before = rtc.now();

    TEST_ASSERT_TRUE(logger.sample());

    float out[10];
    int n = storage.read(before, rtc.now(), 1, out, 10);
    TEST_ASSERT_TRUE(n >= 1);
    TEST_ASSERT_EQUAL_FLOAT(14.7341f, out[n - 1]);
}

void test_sample_fails_without_reading() {
    sensor.value = std::nullopt;    // Simulates a broken sensor.
    TEST_ASSERT_FALSE(logger.sample());
}

void setup() {
    Serial.begin(115200);
    while (!Serial.available()) {
        delay(10);
    }
    Wire.begin();
    rtc.begin();
    storage.begin();
    EventLogger::init("test/log.txt", &rtc);

    UNITY_BEGIN();
    RUN_TEST(test_sample_stores_reading);
    RUN_TEST(test_sample_fails_without_reading);
    UNITY_END();
}

void loop() {}