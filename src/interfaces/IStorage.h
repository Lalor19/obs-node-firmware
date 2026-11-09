#pragma once
#include <time.h>

/** @brief Interface for storage of timestamped readings */
class IStorage {
public:
   virtual ~IStorage() = default;       // Destructor.

   /** @brief Stores one reading, returns false if the write failed. */
   virtual bool write(time_t t, float p) = 0;

   /** 
    * @brief Reads stored values between two times.
    * @param step Take every step-th reading. 
    * @param out Array the readings are stored in.
    * @param max Size of out.
    * @return Amount of values written to out.
    */
   virtual int read(time_t from, time_t to, int step, float* out, int max) = 0;
};