/**
 * @file elevate.ino
 * 
 * @brief main code for running elevate system
 * 
 * @author Jonathan Lee
 * Contact: jonlee27@seas.upenn.edu
 */
#include "elevate_states.h"
#include "button_utility.h"
#include "elevate_module.h"
#include "elevate_system.h"

#define UP_PWM_PIN_0             0
#define DOWN_PWM_PIN_0           0
#define ENCODER_ADC_PIN_0        0
#define UPPER_LIMIT_SWITCH_PIN_0 0
#define LOWER_LIMIT_SWITCH_PIN_0 0
#define UP_PWM_CHANNEL_0         0
#define DOWN_PWM_CHANNEL_0       0

#define UP_PWM_PIN_1             0
#define DOWN_PWM_PIN_1           0
#define ENCODER_ADC_PIN_1        0
#define UPPER_LIMIT_SWITCH_PIN_1 0
#define LOWER_LIMIT_SWITCH_PIN_1 0
#define UP_PWM_CHANNEL_1         0
#define DOWN_PWM_CHANNEL_1       0

#define UP_PWM_PIN_2             0
#define DOWN_PWM_PIN_2           0
#define ENCODER_ADC_PIN_2        0
#define UPPER_LIMIT_SWITCH_PIN_2 0
#define LOWER_LIMIT_SWITCH_PIN_2 0
#define UP_PWM_CHANNEL_2         0
#define DOWN_PWM_CHANNEL_2       0

#define UP_PWM_PIN_3             0
#define DOWN_PWM_PIN_3           0
#define ENCODER_ADC_PIN_3        0
#define UPPER_LIMIT_SWITCH_PIN_3 0
#define LOWER_LIMIT_SWITCH_PIN_3 0
#define UP_PWM_CHANNEL_3         0
#define DOWN_PWM_CHANNEL_3       0

#define UP_BUTTON_PIN   0
#define DOWN_BUTTON_PIN 0

portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;
hw_timer_t *button_panel_timer = NULL;
int const timer_frequency_ms = 10;

uint8_t const NUMBER_OF_MODULES = 4;

bool up_button_pressed() {
  static uint8_t button_state = digitalRead(UP_BUTTON_PIN);
  static uint8_t previous_state = digitalRead(UP_BUTTON_PIN);
  static unsigned long previous_time = millis();
  return button_pressed(UP_BUTTON_PIN, button_state, previous_state, previous_time);
}

bool down_button_pressed() {
  static uint8_t button_state = digitalRead(DOWN_BUTTON_PIN);
  static uint8_t previous_state = digitalRead(DOWN_BUTTON_PIN);
  static unsigned long previous_time = millis();
  return button_pressed(DOWN_BUTTON_PIN, button_state, previous_state, previous_time);
}

void IRAM_ATTR update_system_state() {
  portENTER_CRITICAL_ISR(&mux);
  if (up_button_pressed() && down_button_pressed()) {
    elevate.set_state(STOP);
  } else if (up_button_pressed()) {
    elevate.set_state(MOVE_UP);
  } else if (down_button_pressed()) {
    elevate.set_state(MOVE_DOWN);
  } else {
    elevate.set_state(STOP);
  }
  portEXIT_CRITICAL_ISR(&mux);
}

void setup() {
  // create elevate modules
  ElevateModule modules[NUMBER_OF_MODULES];
  modules[0] = ElevateModule(
    UP_PWM_PIN_0,
    DOWN_PWM_PIN_0,
    ENCODER_ADC_PIN_0,
    UPPER_LIMIT_SWITCH_PIN_0,
    LOWER_LIMIT_SWITCH_PIN_0,
    UP_PWM_CHANNEL_0,
    DOWN_PWM_CHANNEL_0
  );
  modules[1] = ElevateModule(
    UP_PWM_PIN_1,
    DOWN_PWM_PIN_1,
    ENCODER_ADC_PIN_1,
    UPPER_LIMIT_SWITCH_PIN_1,
    LOWER_LIMIT_SWITCH_PIN_1,
    UP_PWM_CHANNEL_1,
    DOWN_PWM_CHANNEL_1
  );
  modules[2] = ElevateModule(
    UP_PWM_PIN_2,
    DOWN_PWM_PIN_2,
    ENCODER_ADC_PIN_2,
    UPPER_LIMIT_SWITCH_PIN_2,
    LOWER_LIMIT_SWITCH_PIN_2,
    UP_PWM_CHANNEL_2,
    DOWN_PWM_CHANNEL_2
  );
  modules[3] = ElevateModule(
    UP_PWM_PIN_3,
    DOWN_PWM_PIN_3,
    ENCODER_ADC_PIN_3,
    UPPER_LIMIT_SWITCH_PIN_3,
    LOWER_LIMIT_SWITCH_PIN_3,
    UP_PWM_CHANNEL_3,
    DOWN_PWM_CHANNEL_3
  );

  // create elevate system
  ElevateSystem elevate = ElevateSystem(modules, NUMBER_OF_MODULES);

  // button panel setup
  pinMode(UP_BUTTON_PIN, INPUT_PULLUP);
  pinMode(DOWN_BUTTON_PIN, INPUT_PULLUP);

  // update system state on fixed interval
  button_panel_timer = timerBegin(0, 80, true);
  timerAttachInterrupt(button_panel_timer, &update_system_state, true);
  timerAlarmWrite(button_panel_timer, 1000 * timer_frequency_ms, true);
  timerAlarmEnable(button_panel_timer);
}

void loop() {
  // elevate system moves based on state
  elevate.control();
}
