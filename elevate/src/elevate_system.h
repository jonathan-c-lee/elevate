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

#include "elevate_types.h"
#include "elevate_module.h"
#include "button_panel.h"

class ElevateSystem {
  public:
    ElevateSystem(ElevateModule* modules, int number_of_modules, ButtonPanel* button_panel);
    void setup();
    void update();
    void control();

  private:
    static float const ROTATIONS_PER_MS;

    ElevateModule* const MODULES;
    int const NUMBER_OF_MODULES;
    ButtonPanel* const BUTTON_PANEL;

    bool is_setup;
    ElevateState state;
    float height;
    unsigned long previous_move_time;

    ElevateStatus get_status() const;
    bool is_module_status(ElevateStatus status) const;
    void set_state(ElevateState state);
    void update_module_status();
    void update_system_state();
    void hard_stop();
    void smooth_stop();
    void move();
    void move_up();
    void move_down();
};

#endif
