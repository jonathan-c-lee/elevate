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

#include "elevate_utils.h"
#include "encoder.h"
#include "pid_controller.h"
#include "i2c_multiplexer.h"
#include <arduino.h>

class ElevateModule {
  public:
    ElevateModule(
      uint8_t up_pwm_pin,
      uint8_t up_pwm_channel,
      uint8_t down_pwm_pin,
      uint8_t down_pwm_channel,
      uint8_t encoder_port,
      uint8_t upper_limit_switch_pin,
      uint8_t lower_limit_switch_pin
    );
    void setup() const;
    ElevateState get_state() const;
    ElevateStatus get_status() const;
    void update_status();
    void hard_stop();
    void smooth_stop(long height);
    void move(long height);

  private:
    static uint32_t const MOTOR_FREQUENCY;
    static uint8_t const MOTOR_RESOLUTION_BITS;

    static float const KP, KI, KD;
    static unsigned long const PID_RATE_MS;
    static int const MINIMUM_OUTPUT, MAXIMUM_OUTPUT;
    static long const ERROR_THRESHOLD;

    static uint8_t const MULTIPLEXER_ADDRESS;
    static I2CMultiplexer const MULTIPLEXER;
    static bool multiplexer_initialized;

    uint8_t const UP_PWM_PIN;
    uint8_t const DOWN_PWM_PIN;
    uint8_t const UPPER_LIMIT_SWITCH_PIN;
    uint8_t const LOWER_LIMIT_SWITCH_PIN;
    uint8_t const UP_PWM_CHANNEL;
    uint8_t const DOWN_PWM_CHANNEL;

    Encoder const ENCODER;

    ElevateState state;
    ElevateStatus status;
    PIDController pid_controller;
    long height;
    int previous_angle;

    void pwm_setup(uint8_t channel, uint8_t pin) const;
    bool upper_limit_switch_pressed() const;
    bool lower_limit_switch_pressed() const;
    int get_angle() const;
    long get_height();
    void set_speed(int speed);
};

#endif
