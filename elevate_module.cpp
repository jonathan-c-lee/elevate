/**
 * @file elevate_module.cpp
 * 
 * @brief elevate leg module
 * 
 * @author Jonathan Lee
 * Contact: jonlee27@seas.upenn.edu
 */
#include "elevate_module.h"
#include "elevate_states.h"
#include <arduino.h>

portMUX_TYPE const ElevateModule::MUX = portMUX_INITIALIZER_UNLOCKED;
uint32_t const ElevateModule::MOTOR_FREQUENCY = 10000;
uint8_t const ElevateModule::MOTOR_RESOLUTION_BITS = 10;
float const ElevateModule::KP = 1.0;
float const ElevateModule::KI = 0.0;
float const ElevateModule::KD = 1.0;

ElevateModule::ElevateModule(
    uint8_t up_pwm_pin,
    uint8_t down_pwm_pin,
    uint8_t encoder_adc_pin,
    uint8_t upper_limit_switch_pin,
    uint8_t lower_limit_switch_pin,
    uint8_t up_pwm_channel,
    uint8_t down_pwm_channel) :
    UP_PWM_PIN(up_pwm_pin),
    DOWN_PWM_PIN(down_pwm_pin),
    ENCODER_ADC_PIN(encoder_adc_pin),
    UPPER_LIMIT_SWITCH_PIN(upper_limit_switch_pin),
    LOWER_LIMIT_SWITCH_PIN(lower_limit_switch_pin),
    UP_PWM_CHANNEL(up_pwm_channel),
    DOWN_PWM_CHANNEL(down_pwm_channel) {
  pwm_setup(up_pwm_channel, up_pwm_pin);
  pwm_setup(down_pwm_channel, down_pwm_pin);
  status = OK;
}

ElevateStatus ElevateModule::get_status() {

}

void ElevateModule::pwm_setup(uint8_t channel, uint8_t pin) {
  ledcSetup(channel, MOTOR_FREQUENCY, MOTOR_RESOLUTION_BITS);
  ledcAttachPin(pin, channel);
  ledcWrite(channel, 0);
}
