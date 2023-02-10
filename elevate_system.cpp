/**
 * @file elevate_system.cpp
 * 
 * @brief elevate system
 * 
 * @author Jonathan Lee
 * Contact: jonlee27@seas.upenn.edu
 */
#include "elevate_system.h"
#include "elevate_states.h"
#include "elevate_module.h"
#include <arduino.h>

unsigned long const ElevateSystem::PID_RATE_MS = 100;

ElevateSystem::ElevateSystem(ElevateModule* modules, uint8_t number_of_modules) :
MODULES(modules), NUMBER_OF_MODULES(number_of_modules) {
  state = STOP;
  height = 0;
}

void ElevateSystem::set_state(ElevateState state) {
  ElevateStatus current_status = get_status();
  switch (state) {
    case STOP:
      this->state = state;
      break;
    case MOVE_UP:
      this->state = (current_status == UPPER_LIMITED) ? STOP : state;
      break;
    case MOVE_DOWN:
      this->state = (current_status == LOWER_LIMITED) ? STOP : state;
      break;
  }
}

void ElevateSystem::control() {
  switch (state) {
    case STOP:
      stop();
      break;
    case MOVE_UP:
      move_up();
      break;
    case MOVE_DOWN:
      move_down();
      break;
  }
}

ElevateStatus get_status() {
  if (is_limited_by_status(LOWER_LIMITED)) {
    return LOWER_LIMITED;
  }
  if (is_limited_by_status(UPPER_LIMITED)) {
    return UPPER_LIMITED;
  }
  return OK;
}

bool ElevateSystem::is_limited_by_status(ElevateStatus status) {
  for (int i = 0; i < NUMBER_OF_MODULES; i++) {
    if (MODULES[i].get_status() == status) return true;
  }
  return false;
}

void ElevateSystem::stop() {

}