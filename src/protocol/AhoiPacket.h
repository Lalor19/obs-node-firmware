/*   Packet layout is based on the ahoi modem's firmware (src/types.h) 
 *   and pylib (lib/ahoi/modem/packet.py), TUHH, BSD 3-Clause license.
 *   https://collaborating.tuhh.de/e-24/public/ahoi/firmware
 *   https://collaborating.tuhh.de/e-24/public/ahoi/pylib
 */

#pragma once
#include <stdint.h>

/** @brief An ahoi packet: 6-byte header + payload. */
struct AhoiPacket {
    static const int HEADER_LEN = 6;
    static const int MAX_PAYLOAD = 128;

    uint8_t src;        // Sender address.
    uint8_t dst;        // Receiver address, 0xFF = broadcast.
    uint8_t type;       // PacketType or CommandType.
    uint8_t status;     // StatusFlag bits.
    uint8_t dsn;        // Sequence number.
    uint8_t len;        // Payload length [bytes].
    uint8_t payload[MAX_PAYLOAD];
};

 /** @brief Writes header + payload as bytes.
  *  @return The byte count, or -1 if out is too small.
  */
int packetToBytes(const AhoiPacket& p, uint8_t* out, int max);

 /** @brief Reads header + payload from bytes.
  *  @return False if the bytes are too short or inconsistent.
  */
bool bytesToPacket(const uint8_t* in, int n, AhoiPacket& p);