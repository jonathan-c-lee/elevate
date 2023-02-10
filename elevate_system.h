/**
 * @file elevate_system.h
 * 
 * @brief header file for elevate system
 * 
 * @author Jonathan Lee
 * Contact: jonlee27@seas.upenn.edu
 */
#ifndef ELEVATE_SYSTEM_H_
#define ELEVATE_SYSTEM_H_

#include "elevate_states.h"
#include "elevate_module.h"
#include <arduino.h>

class ElevateSystem {
  public:
    ElevateSystem(ElevateModule* modules, uint8_t number_of_modules);
    void set_state(ElevateState state);
    void control();

  private:
    static unsigned long const PID_RATE_MS;
    
    ElevateModule* const MODULES;
    uint8_t const NUMBER_OF_MODULES;
    volatile ElevateState state;

    ElevateStatus get_status();
    bool is_limited_by_status(ElevateStatus status);
    void stop();
    void move_up();
    void move_down();
};

#endif
