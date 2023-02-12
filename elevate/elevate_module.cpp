/**
 * @file elevate_module.cpp
 * 
 * @brief elevate leg module
 * 
 * @author Jonathan Lee
 * Contact: jonlee27@seas.upenn.edu
 */
#include "elevate_module.h"
#include "elevate_utils.h"
#include "switch_utility.h"
#include "pid_controller.h"
#include <arduino.h>

uint32_t const ElevateModule::MOTOR_FREQUENCY = 10000;
uint8_t const ElevateModule::MOTOR_RESOLUTION_BITS = 10;

float const ElevateModule::KP = 1.0;
float const ElevateModule::KI = 0.0;
float const ElevateModule::KD = 1.0;
unsigned long const ElevateModule::PID_RATE_MS = 50;
int const ElevateModule::MINIMUM_OUTPUT = (-1 << MOTOR_RESOLUTION_BITS) + 1;
int const ElevateModule::MAXIMUM_OUTPUT = (1 << MOTOR_RESOLUTION_BITS) - 1;
long const ElevateModule::ERROR_THRESHOLD = 10;

/**
 * Elevate Module constructor
 * 
 * @param up_pwm_pin             up pwm pin
 * @param down_pwm_pin           down pwm pin
 * @param encoder_adc_pin        encoder adc input pin
 * @param upper_limit_switch_pin upper limit switch input pin
 * @param lower_limit_switch_pin lower limit switch input pin
 * @param up_pwm_channel         up pwm channel
 * @param down_pwm_channel       down pwm channel
 */
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
    DOWN_PWM_CHANNEL(down_pwm_channel),
    pid_controller(KP, KI, KD, PID_RATE_MS, MINIMUM_OUTPUT, MAXIMUM_OUTPUT) {
  state = STOPPED;
  status = FINE;
  height = 0;
  previous_angle = get_angle();
}

/**
 * Set up module
 */
void ElevateModule::setup() const {
  pwm_setup(UP_PWM_CHANNEL, UP_PWM_PIN);
  pwm_setup(DOWN_PWM_CHANNEL, DOWN_PWM_PIN);
  pinMode(UPPER_LIMIT_SWITCH_PIN, INPUT_PULLUP);
  pinMode(LOWER_LIMIT_SWITCH_PIN, INPUT_PULLUP);
  adcAttachPin(ENCODER_ADC_PIN);
}

/**
 * Get module state
 */
ElevateState ElevateModule::get_state() const {
  return state;
}

/**
 * Get module status
 */
ElevateStatus ElevateModule::get_status() const {
  return status;
}

void ElevateModule::update_status() {
  if (upper_limit_switch_pressed()) {
    status = UPPER_LIMITED;
  } else if (lower_limit_switch_pressed()) {
    status = LOWER_LIMITED;
  } else {
    status = FINE;
  }
}

/**
 * Force stop the module
 */
void ElevateModule::hard_stop() {
  pid_controller.set_mode(OFF);
  set_speed(0);
}

/**
 * Command the module to smoothly stop
 */
void ElevateModule::smooth_stop(long height) {
  if (state == STOPPED) return;
  long current_height = get_height();
  if (abs(current_height - height) < ERROR_THRESHOLD) {
    hard_stop();
  } else {
    pid_controller.set_mode(ON);
    set_speed(pid_controller.control(height, current_height));
  }
}

/**
 * Command the module to move
 */
void ElevateModule::move(long height) {
  pid_controller.set_mode(ON);
  set_speed(pid_controller.control(height, get_height()));
}

/**
 * Set up the pwm pins of the module
 */
void ElevateModule::pwm_setup(uint8_t channel, uint8_t pin) const {
  ledcSetup(channel, MOTOR_FREQUENCY, MOTOR_RESOLUTION_BITS);
  ledcAttachPin(pin, channel);
  ledcWrite(channel, 0);
}

/**
 * Determine if upper limit switch is pressed
 * 
 * @return if upper limit switch is pressed
 */
bool ElevateModule::upper_limit_switch_pressed() const {
  static uint8_t switch_state = digitalRead(UPPER_LIMIT_SWITCH_PIN);
  static uint8_t previous_state = digitalRead(UPPER_LIMIT_SWITCH_PIN);
  static unsigned long previous_time = millis();
  return switch_pressed(UPPER_LIMIT_SWITCH_PIN, switch_state, previous_state, previous_time);
}

/**
 * Determine if lower limit switch is pressed
 * 
 * @return if lower limit switch is pressed
 */
bool ElevateModule::lower_limit_switch_pressed() const {
  static uint8_t switch_state = digitalRead(LOWER_LIMIT_SWITCH_PIN);
  static uint8_t previous_state = digitalRead(LOWER_LIMIT_SWITCH_PIN);
  static unsigned long previous_time = millis();
  return switch_pressed(LOWER_LIMIT_SWITCH_PIN, switch_state, previous_state, previous_time);
}

/**
 * Get the angle of the lead screw
 * 
 * @return angle of the lead screw
 */
int ElevateModule::get_angle() const {
  return analogRead(ENCODER_ADC_PIN);
}

/**
 * Update and get the height of the module
 * 
 * @return height of the module
 */
long ElevateModule::get_height() {
  int current_angle = get_angle();
  int increase = (current_angle - previous_angle + UNITS_PER_ROTATION) % UNITS_PER_ROTATION;
  int decrease = (previous_angle - current_angle + UNITS_PER_ROTATION) % UNITS_PER_ROTATION;
  if (increase > decrease) {
    height -= decrease;
  } else {
    height += increase;
  }
  previous_angle = current_angle;
  return height;
}

/**
 * Set the speed of the module
 * 
 * @param speed speed to set the module at
 */
void ElevateModule::set_speed(int speed) {
  if (speed = 0) {
    ledcWrite(UP_PWM_CHANNEL, 0);
    ledcWrite(DOWN_PWM_CHANNEL, 0);
    state = STOPPED;
  } else if (speed > 0) {
    ledcWrite(UP_PWM_CHANNEL, speed);
    ledcWrite(DOWN_PWM_CHANNEL, 0);
    state = MOVING_UP;
  } else {
    ledcWrite(UP_PWM_CHANNEL, 0);
    ledcWrite(DOWN_PWM_CHANNEL, -speed);
    state = MOVING_DOWN;
  }
}