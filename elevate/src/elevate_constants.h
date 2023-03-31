/**
 * @file elevate_constants.h
 * 
 * @brief constants for elevate
 * 
 * @author Jonathan Lee
 * Contact: jonlee27@seas.upenn.edu
 */
#ifndef ELEVATE_CONSTANTS_H_
#define ELEVATE_CONSTANTS_H_

#include <arduino.h>

// Pin constants
#define PWM_PIN_0                6
#define PWM_CHANNEL_0            0
#define DIRECTION_PIN_0          39
#define ENCODER_PORT_0           0
#define UPPER_LIMIT_SWITCH_PIN_0 21
#define LOWER_LIMIT_SWITCH_PIN_0 5

#define PWM_PIN_1                4
#define PWM_CHANNEL_1            0
#define DIRECTION_PIN_1          5
#define ENCODER_PORT_1           4
#define UPPER_LIMIT_SWITCH_PIN_1 39
#define LOWER_LIMIT_SWITCH_PIN_1 38

#define PWM_PIN_2                4
#define PWM_CHANNEL_2            0
#define DIRECTION_PIN_2          5
#define ENCODER_PORT_2           3
#define UPPER_LIMIT_SWITCH_PIN_2 36
#define LOWER_LIMIT_SWITCH_PIN_2 35

#define PWM_PIN_3                4
#define PWM_CHANNEL_3            0
#define DIRECTION_PIN_3          5
#define ENCODER_PORT_3           2
#define UPPER_LIMIT_SWITCH_PIN_3 34
#define LOWER_LIMIT_SWITCH_PIN_3 33

#define UP_SWITCH_PIN_   35
#define DOWN_SWITCH_PIN_ 37

// Switch constants
unsigned long const DEBOUNCE_DELAY_MS = 25;
unsigned long const USER_INPUT_DELAY_MS = 50;

// Encoder constants
int const UNITS_PER_ROTATION = 1 << 12;
uint8_t const ENCODER_ADDRESS_ = 0x36;
uint8_t const RAW_ANGLE_ADDRESS_ = 0x0c;
uint8_t const STATUS_ADDRESS_ = 0x0b;

// I2C multiplexer constants
int const SDA_PIN = 1;
int const SCL_PIN = 2;

// Elevate module constants
uint32_t const MOTOR_FREQUENCY_ = 10000;
uint8_t const MOTOR_RESOLUTION_BITS_ = 10;
float const KP_ = 2.0;
float const KI_ = 0.2;
float const KD_ = 0.2;
unsigned long const PID_RATE_MS_ = 50;
int const MINIMUM_OUTPUT_ = (-1 << MOTOR_RESOLUTION_BITS_) + 1;
int const MAXIMUM_OUTPUT_ = (1 << MOTOR_RESOLUTION_BITS_) - 1;
long const ERROR_THRESHOLD_ = 10;
uint8_t const MULTIPLEXER_ADDRESS_ = 0x70;

// Elevate system constants
float const ROTATIONS_PER_MS_ = 0.001;

#endif
