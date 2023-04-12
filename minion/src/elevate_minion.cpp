/**
 * @file elevate_minion.cpp
 * 
 * @brief elevate minion
 * 
 * @author Jonathan Lee
 * Contact: jonlee27@seas.upenn.edu
 */
#include "elevate_minion.h"
#include "minion_constants.h"
#include "switch_utility.h"
#include <Arduino.h>

/**
 * Elevate Minion constructor
 * 
 * @param upper_limit_switch_pin upper limit switch input pin
 * @param lower_limit_switch_pin lower limit switch input pin
 */
ElevateMinion::ElevateMinion(uint8_t lower_limit_switch_pin, uint8_t upper_limit_switch_pin) :
encoder(),
UPPER_LIMIT_SWITCH_PIN(upper_limit_switch_pin),
LOWER_LIMIT_SWITCH_PIN(lower_limit_switch_pin) {
  is_setup = false;
  height = 0;
  previous_angle = 0;
}

/**
 * Set up minion
 */
void ElevateMinion::setup() {
  if (!is_setup) {
    pinMode(UPPER_LIMIT_SWITCH_PIN, INPUT);
    pinMode(LOWER_LIMIT_SWITCH_PIN, INPUT);
    previous_angle = encoder.get_raw_angle();
    is_setup = true;
  }
}

/**
 * Determine if lower limit switch is pressed
 * 
 * @return if lower limit switch is pressed
 */
bool ElevateMinion::lower_limit_switch_pressed() const {
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
 * Determine if upper limit switch is pressed
 * 
 * @return if upper limit switch is pressed
 */
bool ElevateMinion::upper_limit_switch_pressed() const {
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
 * Update the height of the module
 * 
 * :return: module height
 */
long ElevateMinion::update_height() {
  int current_angle = encoder.get_raw_angle();
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
