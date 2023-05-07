/**
 * @file elevate_module.cpp
 * 
 * @brief elevate leg module
 * 
 * @author Jonathan Lee
 * Contact: jonlee27@seas.upenn.edu
 */
#include "elevate_module.h"
#include "elevate_constants.h"
#include <Arduino.h>

uint32_t const ElevateModule::MOTOR_FREQUENCY = MOTOR_FREQUENCY_;
uint8_t const ElevateModule::MOTOR_RESOLUTION_BITS = MOTOR_RESOLUTION_BITS_;

float const ElevateModule::KP = KP_;
float const ElevateModule::KI = KI_;
float const ElevateModule::KD = KD_;
unsigned long const ElevateModule::PID_RATE_MS = PID_RATE_MS_;
int const ElevateModule::MINIMUM_OUTPUT = MINIMUM_OUTPUT_;
int const ElevateModule::MAXIMUM_OUTPUT = MAXIMUM_OUTPUT_;
long const ElevateModule::ERROR_THRESHOLD = ERROR_THRESHOLD_;

/**
 * Elevate Module constructor
 * 
 * @param pwm_pin                pwm pin
 * @param pwm_channel            pwm channel
 * @param direction_pin          direction pin
 */
ElevateModule::ElevateModule(uint8_t pwm_pin, uint8_t pwm_channel, uint8_t direction_pin) :
PWM_PIN(pwm_pin),
PWM_CHANNEL(pwm_channel),
DIRECTION_PIN(direction_pin),
pid_controller(KP, KI, KD, PID_RATE_MS, MINIMUM_OUTPUT, MAXIMUM_OUTPUT) {
  is_setup = false;
  state = STOPPED;
  status = FINE;
  height = 0;
  height_offset = 0;
  lower_limit_switch_pressed = false;
  upper_limit_switch_pressed = false;
}

/**
 * Set up module
 */
void ElevateModule::setup() {
  if (!is_setup) {
    pwm_setup(PWM_CHANNEL, PWM_PIN);
    pinMode(DIRECTION_PIN, OUTPUT);
    is_setup = true;
  }
}

/**
 * Get module state
 * 
 * @return module state
 */
ElevateState ElevateModule::get_state() const {
  return state;
}

/**
 * Get module status
 * 
 * @return module status
 */
ElevateStatus ElevateModule::get_status() const {
  return status;
}

/**
 * Update module status
 */
void ElevateModule::update_status() {
  if (upper_limit_switch_pressed && lower_limit_switch_pressed) {
    status = MALFUNCTION;
  } else if (upper_limit_switch_pressed) {
    status = UPPER_LIMITED;
  } else if (lower_limit_switch_pressed) {
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
  state = STOPPED;
}

/**
 * Command the module to smoothly stop
 * 
 * @param height height to stop at
 */
void ElevateModule::smooth_stop(long height) {
  static bool first_call = true;
  static unsigned long start_time = millis();
  if (millis() - start_time > 1.05 * STOP_SETTLE_TIME) {
    first_call = true;
  }
  if (first_call) {
    first_call = false;
    start_time = millis();
  }

  if (state == STOPPED) {
    hard_stop();
  } else if (abs(height - (this->height - this->height_offset)) < ERROR_THRESHOLD) {
    hard_stop();
  } else {
    if (millis() - start_time < STOP_SETTLE_TIME) {
      state = STOPPING;
      move(height);
    } else {
      hard_stop();
    }
  }
}

/**
 * Command the module to move
 * 
 * @param height height to move to
 */
void ElevateModule::move(long height) {
  pid_controller.set_mode(ON);
  set_speed(pid_controller.control(height, this->height - this->height_offset));
}

/**
 * Update module readings
 * 
 * @param height                     new module height from encoder MCU
 * @param lower_limit_switch_pressed whether or not lower limit switch is pressed
 * @param upper_limit_switch_pressed whether or not upper limit switch is pressed
 */
void ElevateModule::update(
    long height,
    bool lower_limit_switch_pressed,
    bool upper_limit_switch_pressed) {
  static unsigned long previous_time = millis();
  unsigned long time_elapsed = millis() - previous_time;
  long height_difference = height - this->height;

  switch (state) {
    case STOPPED:
      previous_time = millis();
      break;
    case STOPPING:
      previous_time = millis();
      break;
    case CALIBRATE:
      previous_time = millis();
      break;
    case MOVING_DOWN:
      if (time_elapsed > 1000) {
        if (height_difference > -(UNITS_PER_ROTATION / 2)) {
          this->height_offset += (time_elapsed / 1000) * UNITS_PER_ROTATION;
        }
      }
      previous_time = millis();
      break;
    case MOVING_UP:
      if (time_elapsed > 1000) {
        if (height_difference < (UNITS_PER_ROTATION / 2)) {
          this->height_offset -= (time_elapsed / 1000) * UNITS_PER_ROTATION;
        }
      }
      previous_time = millis();
      break;
  }

  this->height = height;
  this->lower_limit_switch_pressed = lower_limit_switch_pressed;
  this->upper_limit_switch_pressed = upper_limit_switch_pressed;
}

/**
 * Update the height offset
 */
void ElevateModule::update_offset() {
  height_offset = height;
}

/**
 * Set up the pwm pin of the module
 * 
 * @param channel pwm channel
 * @param pin     pwm pin
 */
void ElevateModule::pwm_setup(uint8_t channel, uint8_t pin) const {
  ledcSetup(channel, MOTOR_FREQUENCY, MOTOR_RESOLUTION_BITS);
  ledcAttachPin(pin, channel);
  ledcWrite(channel, 0);
}

/**
 * Set the speed of the module
 * 
 * @param speed speed to set the module at
 */
void ElevateModule::set_speed(int speed) {
  if (speed == 0) {
    ledcWrite(PWM_CHANNEL, 0);
    state = STOPPED;
  } else if (speed > 0) {
    if (status == UPPER_LIMITED) {
      ledcWrite(PWM_CHANNEL, 0);
      state = STOPPED;
    } else {
      digitalWrite(DIRECTION_PIN, HIGH);
      ledcWrite(PWM_CHANNEL, speed);
      state = MOVING_UP;
    }
  } else {
    if (status == LOWER_LIMITED) {
      ledcWrite(PWM_CHANNEL, 0);
      state = STOPPED;
    } else {
      digitalWrite(DIRECTION_PIN, LOW);
      ledcWrite(PWM_CHANNEL, -speed);
      state = MOVING_DOWN;
    }
  }
}
