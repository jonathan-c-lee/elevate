/**
 * @file minion_constants.h
 * 
 * @brief constants for minion
 * 
 * @author Jonathan Lee
 * Contact: jonlee27@seas.upenn.edu
 */
#ifndef MINION_CONSTANTS_H_
#define MINION_CONSTANTS_H_

#include <stdint.h>

// Pin constants
#define UPPER_LIMIT_SWITCH_PIN_0 15
#define LOWER_LIMIT_SWITCH_PIN_0 14

// Encoder constants
int const SDA_PIN = 18;
int const SCL_PIN = 19;
uint32_t const I2C_FREQUENCY = 100000;
unsigned long const WAIT_TIME_MS = 10;
uint8_t const ENCODER_ADDRESS_ = 0x36;
uint8_t const RAW_ANGLE_ADDRESS_ = 0x0c;
uint8_t const STATUS_ADDRESS_ = 0x0b;

int const UNITS_PER_ROTATION = 1 << 12;
unsigned long const DEBOUNCE_DELAY_MS = 25;

#endif
