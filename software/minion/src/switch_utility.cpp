/**
 * @file switch_utility.cpp
 * 
 * @brief utility functions for general switches
 * 
 * @author Jonathan Lee
 * Contact: jonlee27@seas.upenn.edu
 */
#include "switch_utility.h"
#include <Arduino.h>

/**
 * Determine if a switch is pressed
 * 
 * @param switch_pin     switch input pin
 * @param delay_ms       switch input delay in ms for debounce and/or user feedback
 * @param switch_state   state of the switch
 * @param previous_state previous state of the switch
 * @param previous_time  previous time of state change
 * 
 * @return if switch is pressed
 */
bool switch_pressed(
    uint8_t switch_pin,
    unsigned long delay_ms,
    uint8_t& switch_state,
    uint8_t& previous_state,
    unsigned long& previous_time
) {
  uint8_t current_state = digitalRead(switch_pin);

  if (current_state != previous_state) {
    previous_time = millis();
  }

  if ((millis() - previous_time) > delay_ms) {
    if (current_state != switch_state) {
      switch_state = current_state;
    }
  }

  previous_state = current_state;

  return switch_state == LOW;
}
