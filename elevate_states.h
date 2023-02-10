/**
 * @file elevate_states.h
 * 
 * @brief states for ELEVATE modules and systems
 * 
 * @author Jonathan Lee
 * Contact: jonlee27@seas.upenn.edu
 * 
 */
#ifndef ELEVATE_STATES_H_
#define ELEVATE_STATES_H_

/**
 * Elevate Status
 * 
 * OK:            no limitations
 * LOWER_LIMITED: minimum height reached
 * UPPER_LIMITED: maximum height reached
 */
enum ElevateStatus {
  OK,
  LOWER_LIMITED,
  UPPER_LIMITED
};

/**
 * Elevate State
 * STOP:      no movement
 * MOVE_UP:   upwards movement
 * MOVE_DOWN: downwards movement
 */
enum ElevateState {
  STOP,
  MOVE_UP,
  MOVE_DOWN
};

#endif
