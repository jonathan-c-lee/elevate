/**
 * @file elevate_minion.h
 * 
 * @brief header file for elevate minion
 * 
 * @author Jonathan Lee
 * Contact: jonlee27@seas.upenn.edu
 */
#ifndef ELEVATE_MINION_H_
#define ELEVATE_MINION_H_

#include "encoder.h"

class ElevateMinion {
  public:
    ElevateMinion(uint8_t lower_limit_switch_pin, uint8_t upper_limit_switch_pin);
    void setup();
    bool lower_limit_switch_pressed() const;
    bool upper_limit_switch_pressed() const;
    long update_height();

  private:
    Encoder const encoder;
    uint8_t const UPPER_LIMIT_SWITCH_PIN;
    uint8_t const LOWER_LIMIT_SWITCH_PIN;

    bool is_setup;
    long height;
    int previous_angle;
};

#endif
