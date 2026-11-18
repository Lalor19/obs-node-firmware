/*  Serial framing is based on the ahoi pylib 
 *  (lib/ahoi/com/streamer.py), TUHH, BSD 3-Clause license.
 *  https://collaborating.tuhh.de/e-24/public/ahoi/pylib
 */

 #pragma once
 #include <stdint.h>

 namespace AhoiFrame {
    const uint8_t DLE = 0x10;
    const uint8_t STX = 0x02;
    const uint8_t ETX = 0x03;

    /** 
     * @brief Wraps raw bytes in a frame: DLE STX, data (DLE doubled), DLE ETX.
     * @return Number of bytes written to out, or -1 if out is too small.
     */
    int encode(const uint8_t* in, int len, uint8_t* out, int max);

    /** @brief Reassembles frames from incoming bytes, one at a time. */
    class Decoder {
    public:
        /** @brief Feeds one byte.
         *  @return True when a complete frame is ready.
         */
        bool feed(uint8_t b);

        const uint8_t* data() const { return buf; }
        int length() const { return len; }

    private:
        static const int MAX_FRAME = 160;
        uint8_t buf[MAX_FRAME];
        int len = 0;
        bool afterDle = false;
        bool inFrame = false;
    };
 }