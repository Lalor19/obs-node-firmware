#include <unity.h>
#include "protocol/AhoiFrame.h"
#include "protocol/AhoiPacket.h"

void setUp() {}
void tearDown() {}

void test_encode_stuffs_dle() {
    uint8_t in[] = {0x01, 0x10, 0x02};
    uint8_t out[16];
    int n = AhoiFrame::encode(in, 3, out, sizeof(out));

    uint8_t expected[] = {0x10, 0x02, 0x01, 0x10, 0x10, 0x02, 0x10, 0x03};
    TEST_ASSERT_EQUAL(8, n);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, out, 8);
}

void test_decode_reverses_encode() {
    uint8_t in[] = {0x01, 0x10, 0x02};
    uint8_t framed[16];
    int n = AhoiFrame::encode(in, 3, framed, sizeof(framed));

    AhoiFrame::Decoder dec;
    bool done = false;
    for (int i = 0; i < n; i++) {
        done = dec.feed(framed[i]);
    }
    TEST_ASSERT_TRUE(done);
    TEST_ASSERT_EQUAL(3, dec.length());
    TEST_ASSERT_EQUAL_UINT8_ARRAY(in, dec.data(), 3);
}

void test_packet_encode_decode() {
    AhoiPacket p = {};
    p.src = 1; p.dst = 2; p.type = 0x05; p.dsn = 7; p.len = 2;
    p.payload[0] = 0xAB;
    p.payload[1] = 0x10;

    uint8_t bytes[140];
    int n = packetToBytes(p, bytes, sizeof(bytes));

    AhoiPacket q;
    TEST_ASSERT_TRUE(bytesToPacket(bytes, n, q));
    TEST_ASSERT_EQUAL(2, q.dst);
    TEST_ASSERT_EQUAL(2, q.len);
    TEST_ASSERT_EQUAL_UINT8(0x10, q.payload[1]);
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_encode_stuffs_dle);
    RUN_TEST(test_decode_reverses_encode);
    RUN_TEST(test_packet_encode_decode);
    return UNITY_END();
}