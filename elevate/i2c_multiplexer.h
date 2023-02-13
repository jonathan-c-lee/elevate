/**
 * @file i2c_multiplexer.h
 * 
 * @brief header file for I2C multiplexer
 * 
 * @author Jonathan Lee
 * Contact: jonlee27@seas.upenn.edu
 */
#ifndef I2C_MULTIPLEXER_H_
#define I2C_MULTIPLEXER_H_

#include <arduino.h>

class I2CMultiplexer {
  public:
    I2CMultiplexer(uint8_t address);
    void setup() const;
    void select_device(uint8_t port) const;

  private:
    uint8_t const ADDRESS;
};

#endif
