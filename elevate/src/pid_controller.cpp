/**
 * @file pid_controller.cpp
 * 
 * @brief elevate module PID controller
 * 
 * @author Jonathan Lee
 * Contact: jonlee27@seas.upenn.edu
 */
#include "pid_controller.h"
#include <Arduino.h>

/**
 * PID Controller constructor
 * 
 * @param kp             proportional coefficient
 * @param ki             integral coefficient
 * @param kd             derivative coefficient
 * @param pid_rate_ms    sample time in ms
 * @param minimum_output minimum output value
 * @param maximum_output maximum output value
 */
PIDController::PIDController(
    float kp,
    float ki,
    float kd,
    unsigned long pid_rate_ms,
    int minimum_output,
    int maximum_output) :
    KP(kp),
    KI(ki),
    KD(kd),
    PID_RATE_MS(pid_rate_ms),
    MINIMUM_OUTPUT(minimum_output),
    MAXIMUM_OUTPUT(maximum_output) {
  mode = OFF;
  previous_time = millis();
  integral_term = 0.0;
  previous_input = 0;
  previous_output = 0;
}

/**
 * Set PID controller to ON or OFF
 * 
 * @param mode mode to set PID controller to
 */
void PIDController::set_mode(Mode mode) {
  if (mode == ON && this->mode == OFF) {
    start();
  }
  this->mode = mode;
}

/**
 * Use PID controller to calculate output
 * 
 * @param setpoint setpoint value
 * @param input    input value
 * 
 * @return output of PID controller
 */
int PIDController::control(long setpoint, long input) {
  if (mode == OFF) return previous_output;

  unsigned long current_time = millis();
  if ((current_time - previous_time) >= PID_RATE_MS) {
    long error = setpoint - input;
    integral_term += KI * error;
    if (integral_term > MAXIMUM_OUTPUT) {
      integral_term = MAXIMUM_OUTPUT;
    } else if (integral_term < MINIMUM_OUTPUT) {
      integral_term < MINIMUM_OUTPUT;
    }
    long input_derivative = input - previous_input;

    int output = (int) (KP * error + integral_term - KD * input_derivative);
    if (output > MAXIMUM_OUTPUT) {
      output = MAXIMUM_OUTPUT;
    } else if (output < MINIMUM_OUTPUT) {
      output = MINIMUM_OUTPUT;
    }

    previous_time = current_time;
    previous_input = input;
    previous_output = output;
    return output;
  }
  
  return previous_output;
}

/**
 * Start PID controller when turned ON
 */
void PIDController::start() {
  integral_term = 0.0;
}
