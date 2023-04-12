/**
 * @file encoder.h
 * 
 * @brief header file for encoder
 * 
 * @author Jonathan Lee
 * Contact: jonlee27@seas.upenn.edu
 */
#ifndef ENCODER_H_
#define ENCODER_H_

#include <stdint.h>

/**
 * Magnet Strength
 * 
 * NONE:    not detected
 * WEAK:    too weak
 * PERFECT: perfect strength
 * STRONG:  too strong
 */
enum MagnetStrength {
  NONE,
  WEAK,
  PERFECT,
  STRONG
};

class Encoder {
  public:
    Encoder();
    int get_raw_angle() const;
    bool magnet_detected() const;
    MagnetStrength get_magnet_strength() const;

  private:
    static uint8_t const ENCODER_ADDRESS;
    static uint8_t const RAW_ANGLE_ADDRESS;
    static uint8_t const STATUS_ADDRESS;

    static int read_one_byte(uint8_t address);
    static int read_two_bytes(uint8_t address);
};

#endif
