/**
 * @file encoder.cpp
 * 
 * @brief encoder
 * 
 * @author Jonathan Lee
 * Contact: jonlee27@seas.upenn.edu
 */
#include "encoder.h"
#include <arduino.h>
#include <Wire.h>

uint8_t const Encoder::ENCODER_ADDRESS = 0x36;
uint8_t const Encoder::RAW_ANGLE_ADDRESS = 0x0c;
uint8_t const Encoder::STATUS_ADDRESS = 0x0b;

/**
 * Encoder constructor
 * 
 * @param port port on I2C multiplexer
 */
Encoder::Encoder(uint8_t port) : PORT(port) {}

/**
 * Get I2C multiplexer port
 * 
 * @return I2C multiplexer port
 */
uint8_t Encoder::get_port() const {
  return PORT;
}

/**
 * Get raw angle, 0-4095
 * 
 * @return raw angle
 */
int Encoder::get_raw_angle() const {
  return read_two_bytes(RAW_ANGLE_ADDRESS);
}

/**
 * Check if magnet is detected
 * 
 * @return if magnet is detected
 */
bool Encoder::magnet_detected() const {
  int status = read_one_byte(STATUS_ADDRESS);
  return (status & 0x20);
}

/**
 * Check magnet strength
 * 
 * @return magnet strength
 */
MagnetStrength Encoder::get_magnet_strength() const {
  MagnetStrength strength = NONE;
  int status = read_one_byte(STATUS_ADDRESS);
  if (status & 0x20) {
    strength = PERFECT;
    if (status & 0x10) {
      strength = WEAK;
    } else if (status & 0x08) {
      strength = STRONG;
    }
  }

  return strength;
}

/**
 * Read one byte of information from encoder
 * 
 * @param address address to read from
 * 
 * @return one byte of information
 */
int Encoder::read_one_byte(uint8_t address) {
  Wire.beginTransmission(ENCODER_ADDRESS);
  Wire.write(address);
  Wire.endTransmission();
  Wire.requestFrom(ENCODER_ADDRESS, (uint8_t) 1);
  while (Wire.available() == 0);
  return (int) Wire.read();
}

/**
 * Read two bytes of information from encoder
 * 
 * @param address address to read from
 * 
 * @return two bytes of information
 */
int Encoder::read_two_bytes(uint8_t address) {
  Wire.beginTransmission(ENCODER_ADDRESS);
  Wire.write(address);
  Wire.endTransmission();
  Wire.requestFrom(ENCODER_ADDRESS, (uint8_t) 2);
  while (Wire.available() < 2);
  int high_byte = Wire.read();
  int low_byte = Wire.read();
  return (high_byte << 8) | low_byte;
}
