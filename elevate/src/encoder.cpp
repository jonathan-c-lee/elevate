/**
 * @file encoder.cpp
 * 
 * @brief encoder
 * 
 * @author Jonathan Lee
 * Contact: jonlee27@seas.upenn.edu
 */
#include "encoder.h"
#include "elevate_constants.h"
#include <arduino.h>
#include <Wire.h>

uint8_t const Encoder::ENCODER_ADDRESS = ENCODER_ADDRESS_;
uint8_t const Encoder::RAW_ANGLE_ADDRESS = RAW_ANGLE_ADDRESS_;
uint8_t const Encoder::STATUS_ADDRESS = STATUS_ADDRESS_;

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
  static int reading = 0;
  Wire.beginTransmission(ENCODER_ADDRESS);
  Wire.write(address);
  Wire.endTransmission();
  Wire.requestFrom(ENCODER_ADDRESS, (uint8_t) 1);
  unsigned long start = millis();
  while (Wire.available() == 0) {
    if (millis() - start > WAIT_TIME_MS) return reading;
  };
  reading = (int) Wire.read();
  return reading;
}

/**
 * Read two bytes of information from encoder
 * 
 * @param address address to read from
 * 
 * @return two bytes of information
 */
int Encoder::read_two_bytes(uint8_t address) {
  static int reading = 0;
  Wire.beginTransmission(ENCODER_ADDRESS);
  Wire.write(address);
  Wire.endTransmission();
  Wire.requestFrom(ENCODER_ADDRESS, (uint8_t) 2);
  unsigned long start = millis();
  while (Wire.available() < 2) {
    if (millis() - start > WAIT_TIME_MS) return reading;
  };
  int high_byte = Wire.read();
  int low_byte = Wire.read();
  Serial.println("exit read 2 bytes");
  reading = (high_byte << 8) | low_byte;
  return reading;
}
