/**
 * @file button_panel.cpp
 * 
 * @brief button panel
 * 
 * @author Jonathan Lee
 * Contact: jonlee27@seas.upenn.edu
 */
#include "button_panel.h"
#include "elevate_constants.h"
#include "switch_utility.h"
#include <Arduino.h>

/**
 * Button Panel constructor
 * 
 * @param up_switch_pin   up switch input pin
 * @param down_switch_pin down switch input pin
 */
ButtonPanel::ButtonPanel(uint8_t up_switch_pin, uint8_t down_switch_pin) :
UP_SWITCH_PIN(up_switch_pin), DOWN_SWITCH_PIN(down_switch_pin) {}

/**
 * Set up button panel
 */
void ButtonPanel::setup() const {
  pinMode(UP_SWITCH_PIN, INPUT);
  pinMode(DOWN_SWITCH_PIN, INPUT);
}

/**
 * Determine if up switch is pressed
 * 
 * @return if up switch is pressed
 */
bool ButtonPanel::up_switch_pressed() const {
  static uint8_t switch_state = digitalRead(UP_SWITCH_PIN);
  static uint8_t previous_state = digitalRead(UP_SWITCH_PIN);
  static unsigned long previous_time = millis();
  return switch_pressed(
    UP_SWITCH_PIN,
    USER_INPUT_DELAY_MS,
    switch_state,
    previous_state,
    previous_time
  );
}

/**
 * Determine if down switch is pressed
 * 
 * @return if down switch is pressed
 */
bool ButtonPanel::down_switch_pressed() const {
  static uint8_t switch_state = digitalRead(DOWN_SWITCH_PIN);
  static uint8_t previous_state = digitalRead(DOWN_SWITCH_PIN);
  static unsigned long previous_time = millis();
  return switch_pressed(
    DOWN_SWITCH_PIN,
    USER_INPUT_DELAY_MS,
    switch_state,
    previous_state,
    previous_time
  );
}
