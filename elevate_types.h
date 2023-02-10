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
 * OK:            no limitations
 * UPPER_LIMITED: maximum height reached
 * LOWER_LIMITED: minimum height reached
 */
enum ElevateStatus {
  OK,
  UPPER_LIMITED,
  LOWER_LIMITED
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
