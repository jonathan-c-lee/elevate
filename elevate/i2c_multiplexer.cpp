/**
 * @file i2c_multiplexer.cpp
 * 
 * @brief I2C multiplexer
 * 
 * @author Jonathan Lee
 * Contact: jonlee27@seas.upenn.edu
 */
#include "i2c_multiplexer.h"
#include <arduino.h>
#include <Wire.h>

int const SDA_PIN = 1;
int const SCL_PIN = 2;

/**
 * I2C Multiplexer constructor
 * 
 * @param address address of I2C multiplexer
 */
I2CMultiplexer::I2CMultiplexer(uint8_t address) : ADDRESS(address) {}

/**
 * Set up I2C multiplexer
 */
void I2CMultiplexer::setup() const {
  Wire.setPins(SDA_PIN, SCL_PIN);
  Wire.begin();
}

/**
 * Select I2C device
 * 
 * @param port port on multiplexer of I2C device
 */
void I2CMultiplexer::select_device(uint8_t port) const {
  if (port > 7) return;
  Wire.beginTransmission(ADDRESS);
  Wire.write(1 << port);
  Wire.endTransmission();
}
