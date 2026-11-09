#pragma once

/** @brief Interface for a communication link that sends and receives raw bytes. */
class ILink {
public:
    virtual ~ILink() = default;
    
    /**
     * @brief Receives incoming data.
     * @param buf Array the received bytes are stored in.
     * @param len Size of buf.
     * @return Amount of bytes received, 0 if nothing arrived.
     */
    virtual int receive(char* buf, int len) = 0;
    
    /** 
     * @brief Sends len bytes from buf.
     * @return False if sending failed.
     */
    virtual bool send(const char* buf, int len) = 0;
};