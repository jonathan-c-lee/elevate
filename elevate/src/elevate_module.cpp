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
#include "switch_utility.h"
#include <arduino.h>

uint32_t const ElevateModule::MOTOR_FREQUENCY = MOTOR_FREQUENCY_;
uint8_t const ElevateModule::MOTOR_RESOLUTION_BITS = MOTOR_RESOLUTION_BITS_;

float const ElevateModule::KP = KP_;
float const ElevateModule::KI = KI_;
float const ElevateModule::KD = KD_;
unsigned long const ElevateModule::PID_RATE_MS = PID_RATE_MS_;
int const ElevateModule::MINIMUM_OUTPUT = MINIMUM_OUTPUT_;
int const ElevateModule::MAXIMUM_OUTPUT = MAXIMUM_OUTPUT_;
long const ElevateModule::ERROR_THRESHOLD = ERROR_THRESHOLD_;

uint8_t const ElevateModule::MULTIPLEXER_ADDRESS = MULTIPLEXER_ADDRESS_;
I2CMultiplexer ElevateModule::MULTIPLEXER = I2CMultiplexer(MULTIPLEXER_ADDRESS);

/**
 * Elevate Module constructor
 * 
 * @param pwm_pin                pwm pin
 * @param pwm_channel            pwm channel
 * @param direction_pin          direction pin
 * @param encoder_port           encoder port on I2C multiplexer
 * @param upper_limit_switch_pin upper limit switch input pin
 * @param lower_limit_switch_pin lower limit switch input pin
 */
ElevateModule::ElevateModule(
    uint8_t pwm_pin,
    uint8_t pwm_channel,
    uint8_t direction_pin,
    uint8_t encoder_port,
    uint8_t upper_limit_switch_pin,
    uint8_t lower_limit_switch_pin) :
    PWM_PIN(pwm_pin),
    PWM_CHANNEL(pwm_channel),
    DIRECTION_PIN(direction_pin),
    ENCODER(encoder_port),
    UPPER_LIMIT_SWITCH_PIN(upper_limit_switch_pin),
    LOWER_LIMIT_SWITCH_PIN(lower_limit_switch_pin),
    pid_controller(KP, KI, KD, PID_RATE_MS, MINIMUM_OUTPUT, MAXIMUM_OUTPUT) {
  is_setup = false;
  state = STOPPED;
  status = FINE;
  height = 0;
  previous_angle = 0;
}

/**
 * Set up module
 */
void ElevateModule::setup() {
  if (!is_setup) {
    pwm_setup(PWM_CHANNEL, PWM_PIN);
    pinMode(DIRECTION_PIN, OUTPUT);
    pinMode(UPPER_LIMIT_SWITCH_PIN, INPUT);
    pinMode(LOWER_LIMIT_SWITCH_PIN, INPUT);
    //MULTIPLEXER.setup();
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
  if (upper_limit_switch_pressed() && lower_limit_switch_pressed()) {
    status = MALFUNCTION;
  } else if (upper_limit_switch_pressed()) {
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
 * 
 * @param height height to stop at
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
 * 
 * @param height height to move to
 */
void ElevateModule::move(long height) {
  pid_controller.set_mode(ON);
  Serial.print("DESIRED: ");
  Serial.println(height);
  Serial.print("CURRENT: ");
  Serial.println(get_height());
  set_speed(pid_controller.control(height, get_height()));
  // set_speed(height);
}

/**
 * Update the height of the module
 * 
 * :param current_angle: the current angle reading
 * :return: module height
 */
long ElevateModule::update_height(int current_angle) {
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
 * Determine if upper limit switch is pressed
 * 
 * @return if upper limit switch is pressed
 */
bool ElevateModule::upper_limit_switch_pressed() const {
  static uint8_t switch_state = digitalRead(UPPER_LIMIT_SWITCH_PIN);
  static uint8_t previous_state = digitalRead(UPPER_LIMIT_SWITCH_PIN);
  static unsigned long previous_time = millis();
  return switch_pressed(
    UPPER_LIMIT_SWITCH_PIN,
    DEBOUNCE_DELAY_MS,
    switch_state,
    previous_state,
    previous_time
  );
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
  return switch_pressed(
    LOWER_LIMIT_SWITCH_PIN,
    DEBOUNCE_DELAY_MS,
    switch_state,
    previous_state,
    previous_time
  );
}

/**
 * Get the angle of the lead screw
 * 
 * @return angle of the lead screw
 */
int ElevateModule::get_angle() const {
  MULTIPLEXER.select_device(ENCODER.get_port());
  return ENCODER.get_raw_angle();
}

/**
 * Get the height of the module
 * 
 * @return height of the module
 */
long ElevateModule::get_height() {
  return height;
}

/**
 * Set the speed of the module
 * 
 * @param speed speed to set the module at
 */
void ElevateModule::set_speed(int speed) {
  Serial.print("SPEED: ");
  Serial.println(speed);
  if (speed == 0) {
    ledcWrite(PWM_CHANNEL, 0);
    state = STOPPED;
  } else if (speed > 0) {
    digitalWrite(DIRECTION_PIN, HIGH);
    ledcWrite(PWM_CHANNEL, speed);
    // ledcWrite(PWM_CHANNEL, 500);
    state = MOVING_UP;
  } else {
    digitalWrite(DIRECTION_PIN, LOW);
    ledcWrite(PWM_CHANNEL, -speed);
    // ledcWrite(PWM_CHANNEL, 500);
    state = MOVING_DOWN;
  }
}
