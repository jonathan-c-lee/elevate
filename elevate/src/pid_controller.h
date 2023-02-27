/**
 * @file pid_controller.h
 * 
 * @brief header file for elevate module PID controller
 * 
 * @author Jonathan Lee
 * Contact: jonlee27@seas.upenn.edu
 */
#ifndef PID_CONTROLLER_H_
#define PID_CONTROLLER_H_

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

class PIDController {
  public:
    PIDController(
      float kp,
      float ki,
      float kd,
      unsigned long pid_rate_ms,
      int minimum_output,
      int maximum_output
    );
    void set_mode(Mode mode);
    int control(long setpoint, long input);

  private:
    float const KP, KI, KD;
    unsigned long const PID_RATE_MS;
    int const MINIMUM_OUTPUT, MAXIMUM_OUTPUT;
    
    Mode mode;
    unsigned long previous_time;
    float integral_term;
    long previous_input;
    int previous_output;
    
    void start();
};

#endif
