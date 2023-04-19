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
#define PWM_PIN_0       16
#define PWM_CHANNEL_0   0
#define DIRECTION_PIN_0 13

#define PWM_PIN_1       15
#define PWM_CHANNEL_1   1
#define DIRECTION_PIN_1 12

#define PWM_PIN_2       39
#define PWM_CHANNEL_2   2
#define DIRECTION_PIN_2 41

#define PWM_PIN_3       40
#define PWM_CHANNEL_3   3
#define DIRECTION_PIN_3 42

#define UP_SWITCH_PIN_   36
#define DOWN_SWITCH_PIN_ 37

// Switch constants
unsigned long const USER_INPUT_DELAY_MS = 50;

// Elevate module constants
uint32_t const MOTOR_FREQUENCY_ = 10000;
uint8_t const MOTOR_RESOLUTION_BITS_ = 10;
float const KP_ = 1.25;
float const KI_ = 0.00;
float const KD_ = 0.15;
unsigned long const PID_RATE_MS_ = 50;
int const MINIMUM_OUTPUT_ = -(1 << MOTOR_RESOLUTION_BITS_) + 1;
int const MAXIMUM_OUTPUT_ = (1 << MOTOR_RESOLUTION_BITS_) - 1;
long const ERROR_THRESHOLD_ = 5;

// Elevate system constants
int const UNITS_PER_ROTATION = 1 << 12;
float const ROTATIONS_PER_MS_ = 0.001;

#endif
