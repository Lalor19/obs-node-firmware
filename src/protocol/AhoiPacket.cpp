#include "AhoiPacket.h"
#include <string.h>

int packetToBytes(const AhoiPacket& p, uint8_t* out, int max) {
    int n = AhoiPacket::HEADER_LEN + p.len;
    if (n > max) {
        return -1;
    }
    out[0] = p.src;
    out[1] = p.dst;
    out[2] = p.type;
    out[3] = p.status;
    out[4] = p.dsn;
    out[5] = p.len;
    memcpy(out + AhoiPacket::HEADER_LEN, p.payload, p.len);
    return n;
}

bool bytesToPacket(const uint8_t* in, int n, AhoiPacket& p) {
    if (n < AhoiPacket::HEADER_LEN) {
        return false;
    }
    p.src = in[0];
    p.dst = in[1];
    p.type = in[2];
    p.status = in[3];
    p.dsn = in[4];
    p.len = in[5];
    if (p.len > AhoiPacket::MAX_PAYLOAD || AhoiPacket::HEADER_LEN + p.len > n) {
        return false;
    }
    memcpy(p.payload, in + AhoiPacket::HEADER_LEN, p.len);
    return true;
}