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

#include <stdint.h>

// Pin constants
#define PWM_PIN_0                16
#define PWM_CHANNEL_0            0
#define DIRECTION_PIN_0          3

#define PWM_PIN_1                4
#define PWM_CHANNEL_1            0
#define DIRECTION_PIN_1          5

#define PWM_PIN_2                4
#define PWM_CHANNEL_2            0
#define DIRECTION_PIN_2          5

#define PWM_PIN_3                4
#define PWM_CHANNEL_3            0
#define DIRECTION_PIN_3          5

#define UP_SWITCH_PIN_   41
#define DOWN_SWITCH_PIN_ 42

// Switch constants
unsigned long const USER_INPUT_DELAY_MS = 50;

// Elevate module constants
uint32_t const MOTOR_FREQUENCY_ = 10000;
uint8_t const MOTOR_RESOLUTION_BITS_ = 10;
float const KP_ = 2.0;
float const KI_ = 0.2;
float const KD_ = 0.2;
unsigned long const PID_RATE_MS_ = 50;
int const MINIMUM_OUTPUT_ = -(1 << MOTOR_RESOLUTION_BITS_) + 1;
int const MAXIMUM_OUTPUT_ = (1 << MOTOR_RESOLUTION_BITS_) - 1;
long const ERROR_THRESHOLD_ = 20;

// Elevate system constants
int const UNITS_PER_ROTATION = 1 << 12;
float const ROTATIONS_PER_MS_ = 0.001;

#endif
