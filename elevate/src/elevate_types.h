/**
 * @file elevate_types.h
 * 
 * @brief types for ELEVATE modules and systems
 * 
 * @author Jonathan Lee
 * Contact: jonlee27@seas.upenn.edu
 */
#ifndef ELEVATE_TYPES_H_
#define ELEVATE_TYPES_H_

/**
 * Elevate Status
 * 
 * FINE:          no limitations
 * UPPER_LIMITED: maximum height reached
 * LOWER_LIMITED: minimum height reached
 * MALFUNCTION:   system failure
 */
enum ElevateStatus {
  FINE,
  UPPER_LIMITED,
  LOWER_LIMITED,
  MALFUNCTION
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

#endif
