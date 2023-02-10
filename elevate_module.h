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

#include "elevate_states.h"
#include <arduino.h>

class ElevateModule {
  public:
    ElevateModule(
      uint8_t up_pwm_pin,
      uint8_t down_pwm_pin,
      uint8_t encoder_adc_pin,
      uint8_t upper_limit_switch_pin,
      uint8_t lower_limit_switch_pin,
      uint8_t up_pwm_channel,
      uint8_t down_pwm_channel
    );
    ElevateStatus get_status();

  private:
    static portMUX_TYPE const MUX;
    static uint32_t const MOTOR_FREQUENCY;
    static uint8_t const MOTOR_RESOLUTION_BITS;
    static float const KP, KI, KD;

    uint8_t const UP_PWM_PIN;
    uint8_t const DOWN_PWM_PIN;
    uint8_t const ENCODER_ADC_PIN;
    uint8_t const UPPER_LIMIT_SWITCH_PIN;
    uint8_t const LOWER_LIMIT_SWITCH_PIN;
    uint8_t const UP_PWM_CHANNEL;
    uint8_t const DOWN_PWM_CHANNEL;

    void pwm_setup(uint8_t channel, uint8_t pin);
    bool is_upper_limited();
    bool is_lower_limited();
};

#endif
