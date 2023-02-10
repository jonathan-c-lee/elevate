/**
 * @file button_utility.cpp
 * 
 * @brief utility functions for general buttons
 * 
 * @author Jonathan Lee
 * Contact: jonlee27@seas.upenn.edu
 */
#include "button_utility.h"
#include <arduino.h>

bool button_pressed(
    uint8_t button_pin,
    uint8_t& button_state,
    uint8_t& previous_state,
    unsigned long& previous_time
) {
  uint8_t current_state = digitalRead(button_pin);

  if (current_state != previous_state) {
    previous_time = millis();
  }

  if ((millis() - previous_time) > DEBOUNCE_DELAY_MS) {
    if (current_state != button_state) {
      button_state = current_state;
    }
  }

  previous_state = current_state;

  return button_state == HIGH;
}
