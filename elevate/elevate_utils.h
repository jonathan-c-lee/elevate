/**
 * @file elevate_utils.h
 * 
 * @brief constants and types for ELEVATE modules and systems
 * 
 * @author Jonathan Lee
 * Contact: jonlee27@seas.upenn.edu
 */
#ifndef ELEVATE_UTILS_H_
#define ELEVATE_UTILS_H_

int const UNITS_PER_ROTATION = 1 << 12;

/**
 * Elevate Status
 * 
 * FINE:          no limitations
 * UPPER_LIMITED: maximum height reached
 * LOWER_LIMITED: minimum height reached
 */
enum ElevateStatus {
  FINE,
  UPPER_LIMITED,
  LOWER_LIMITED
};

/**
 * Elevate State
 * 
 * STOPPED:     no movement
 * STOPPING:    preparing to stop
 * MOVING_UP:   moving upwards
 * MOVING_DOWN: moving downwards
 */
enum ElevateState {
  STOPPED,
  STOPPING,
  MOVING_UP,
  MOVING_DOWN
};

/**
 * Mode for PID controller
 * 
 * ON:  PID controller is on
 * OFF: PID controller is off
 */
enum Mode {
  ON,
  OFF
};

#endif
