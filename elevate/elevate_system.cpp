/**
 * @file elevate_system.cpp
 * 
 * @brief elevate system
 * 
 * @author Jonathan Lee
 * Contact: jonlee27@seas.upenn.edu
 */
#include "elevate_system.h"
#include "elevate_utils.h"
#include "elevate_module.h"
#include "button_panel.h"
#include <arduino.h>

float const ElevateSystem::ROTATIONS_PER_MS = 0.001;

/**
 * Elevate System constructor
 * 
 * @param modules           pointer to array of modules
 * @param number_of_modules number of modules in system
 * @param button_panel      pointer to button panel
 */
ElevateSystem::ElevateSystem(
    ElevateModule* modules,
    int number_of_modules,
    ButtonPanel* button_panel) :
    MODULES(modules),
    NUMBER_OF_MODULES(number_of_modules),
    BUTTON_PANEL(button_panel) {
  state = STOPPED;
  height = 0.0;
  previous_move_time = micros();
}

/**
 * Set up system
 */
void ElevateSystem::setup() {
  BUTTON_PANEL->setup();
  for (int i = 0; i < NUMBER_OF_MODULES; i++) {
    MODULES[i].setup();
  }
}

/**
 * Update the state and status of the system
 */
void ElevateSystem::update() {
  update_module_status();
  update_system_state();
}

/**
 * Control the system based on its state
 */
void ElevateSystem::control() {
  switch (state) {
    case STOPPED:
      hard_stop();
      break;
    case STOPPING:
      smooth_stop();
      break;
    case MOVING_UP:
      move_up();
      break;
    case MOVING_DOWN:
      move_down();
      break;
  }
}

/**
 * Get the status of the system
 * 
 * @return system status
 */
ElevateStatus ElevateSystem::get_status() const {
  if (is_limited_by_status(LOWER_LIMITED)) {
    return LOWER_LIMITED;
  }
  if (is_limited_by_status(UPPER_LIMITED)) {
    return UPPER_LIMITED;
  }
  return FINE;
}

/**
 * Determine if the system is limited by a given status
 * 
 * @param status given status
 * 
 * @return if the system is limited by the given status
 */
bool ElevateSystem::is_limited_by_status(ElevateStatus status) const {
  for (int i = 0; i < NUMBER_OF_MODULES; i++) {
    if (MODULES[i].get_status() == status) return true;
  }
  return false;
}

/**
 * Set the state of the system
 * 
 * @param state given state
 */
void ElevateSystem::set_state(ElevateState state) {
  ElevateState current_state = this->state;
  ElevateStatus current_status = get_status();
  switch (state) {
    case STOPPED:
      this->state = state;
      break;
    case STOPPING:
      this->state = (this->state == STOPPED) ? STOPPED : STOPPING;
      break;
    case MOVING_UP:
      this->state = (current_status == UPPER_LIMITED) ? STOPPED : MOVING_UP;
      if (current_state != MOVING_UP) previous_move_time = micros();
      break;
    case MOVING_DOWN:
      this->state = (current_status == LOWER_LIMITED) ? STOPPED : MOVING_DOWN;
      if (current_state != MOVING_DOWN) previous_move_time = micros();
      break;
  }
}

/**
 * Update the status of all modules in the system
 */
void ElevateSystem::update_module_status() {
  for (int i = 0; i < NUMBER_OF_MODULES; i++) {
    MODULES[i].update_status();
  }
}

/**
 * Update the state of the system based on button panel input
 */
void ElevateSystem::update_system_state() {
  if (BUTTON_PANEL->up_switch_pressed() && BUTTON_PANEL->down_switch_pressed()) {
    set_state(STOPPING);
  } else if (BUTTON_PANEL->up_switch_pressed()) {
    set_state(MOVING_UP);
  } else if (BUTTON_PANEL->down_switch_pressed()) {
    set_state(MOVING_DOWN);
  } else {
    set_state(STOPPING);
  }
}

/**
 * Force stop the system
 */
void ElevateSystem::hard_stop() {
  for (int i = 0; i < NUMBER_OF_MODULES; i++) {
    MODULES[i].hard_stop();
  }
}

/**
 * Command the system to smoothly stop
 */
void ElevateSystem::smooth_stop() {
  for (int i = 0; i < NUMBER_OF_MODULES; i++) {
    MODULES[i].smooth_stop((long) height);
  }
  for (int i = 0; i < NUMBER_OF_MODULES; i++) {
    if (MODULES[i].get_state() != STOPPED) return;
  }
  state = STOPPED;
}

/**
 * Command the system to move
 */
void ElevateSystem::move() {
  for (int i = 0; i < NUMBER_OF_MODULES; i++) {
    MODULES[i].move((long) height);
  }
}

/**
 * Command the system to move up
 */
void ElevateSystem::move_up() {
  unsigned long current_time = micros();
  height += UNITS_PER_ROTATION * ROTATIONS_PER_MS * (current_time - previous_move_time) * 1e-3;
  previous_move_time = current_time;
  move();
}

/**
 * Command the system to move down
 */
void ElevateSystem::move_down() {
  unsigned long current_time = micros();
  height -= UNITS_PER_ROTATION * ROTATIONS_PER_MS * (current_time - previous_move_time) * 1e-3;
  previous_move_time = current_time;
  move();
}
