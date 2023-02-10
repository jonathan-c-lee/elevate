/**
 * @file button_utility.h
 * 
 * @brief header file for utility functions for general buttons
 * 
 * @author Jonathan Lee
 * Contact: jonlee27@seas.upenn.edu
 */
#ifndef BUTTON_UTILITY_H_
#define BUTTON_UTILITY_H_

#include <arduino.h>

unsigned long const DEBOUNCE_DELAY_MS = 25;

bool button_pressed(
    uint8_t button_pin,
    uint8_t& button_state,
    uint8_t& previous_state,
    unsigned long& previous_time
);

#endif
