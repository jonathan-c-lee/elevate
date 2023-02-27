/**
 * @file switch_utility.h
 * 
 * @brief header file for utility functions for general switches
 * 
 * @author Jonathan Lee
 * Contact: jonlee27@seas.upenn.edu
 */
#ifndef SWITCH_UTILITY_H_
#define SWITCH_UTILITY_H_

#include <arduino.h>

bool switch_pressed(
    uint8_t switch_pin,
    unsigned long delay_ms,
    uint8_t& switch_state,
    uint8_t& previous_state,
    unsigned long& previous_time
);

#endif
