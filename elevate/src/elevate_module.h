/**
 * @file elevate_module.h
 * 
 * @brief header file for elevate leg module
 * 
 * @author Jonathan Lee
 * Contact: jonlee27@seas.upenn.edu
 */
#ifndef ELEVATE_MODULE_H_
#define ELEVATE_MODULE_H_

#include "elevate_types.h"
#include "pid_controller.h"
#include <stdint.h>

class ElevateModule {
  public:
    ElevateModule(uint8_t pwm_pin, uint8_t pwm_channel, uint8_t direction_pin);
    void setup();
    ElevateState get_state() const;
    ElevateStatus get_status() const;
    void update_status();
    void hard_stop();
    void smooth_stop(long height);
    void move(long height);
    void update(long height, bool lower_limit_switch_pressed, bool upper_limit_switch_pressed);
    void update_offset();

  private:
    static uint32_t const MOTOR_FREQUENCY;
    static uint8_t const MOTOR_RESOLUTION_BITS;

    static float const KP, KI, KD;
    static unsigned long const PID_RATE_MS;
    static int const MINIMUM_OUTPUT, MAXIMUM_OUTPUT;
    static long const ERROR_THRESHOLD;

    uint8_t const PWM_PIN;
    uint8_t const PWM_CHANNEL;
    uint8_t const DIRECTION_PIN;

    bool is_setup;
    ElevateState state;
    ElevateStatus status;
    PIDController pid_controller;
    volatile long height;
    long height_offset;
    volatile bool lower_limit_switch_pressed;
    volatile bool upper_limit_switch_pressed;

    void pwm_setup(uint8_t channel, uint8_t pin) const;
    void set_speed(int speed);
};

#endif
