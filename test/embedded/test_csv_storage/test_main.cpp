#include <Arduino.h>
#include <unity.h>
#include <SD.h>
#include "hardware/CsvStorage.h"

CsvStorage storage ("test");

void test_write_and_read() {
    TEST_ASSERT_TRUE(storage.begin());

    SD.remove("test/20261116.csv");     // Remove former test files.

    time_t t = 1794355200;
    TEST_ASSERT_TRUE(storage.write(t, 12.5f));

    float out[1];
    int n = storage.read(t, t, 1, out, 1);

    TEST_ASSERT_EQUAL(1, n);
    TEST_ASSERT_EQUAL_FLOAT(12.5F, out[0]);
}

void setup() {
    Serial.begin(115200);
    while (!Serial.available()) {
        delay(10);
    }

    UNITY_BEGIN();
    RUN_TEST(test_write_and_read);
    UNITY_END();
}

void loop() {}

