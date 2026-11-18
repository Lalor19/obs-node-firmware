#include "AhoiFrame.h"

namespace AhoiFrame{
    int encode(const uint8_t* in, int len, uint8_t* out, int max) {
        int n = 0;
        if (max < 4) {
            return -1;
        }
        out[n++] = DLE;
        out[n++] = STX;
        for (int i = 0; i < len; i++) {
            if (n + 4 > max) {
                return -1;
            }
            out[n++] = in[i];
            if (in[i] == DLE) {
                out[n++] = DLE;
            }
        }
        out[n++] = DLE;
        out[n++] = ETX;
        return n;
    }

    bool Decoder::feed(uint8_t b) {
        if (!afterDle) {
            if (b == DLE) {
                afterDle = true;
            } else if (inFrame && len < MAX_FRAME) {
                buf[len++] = b;
            }
            return false;
        }
        afterDle = false;

        if (b == STX && !inFrame) {     // Frame start.
            inFrame = true;
            len = 0;
        } else if (b == ETX && inFrame) {       // Frame end.
            inFrame = false;
            return true;
        } else if (b == DLE && inFrame) {       // 0x10 data byte.
            if (len < MAX_FRAME) {
                buf[len++] = b;
            }
        } else if (inFrame) {       // Invalid sequence: drop frame.
            inFrame = false;
            len = 0;
        }
        return false;
    }

}