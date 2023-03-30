/**
 * @file elevate.ino
 * 
 * @brief main code for running elevate system
 * 
 * @author Jonathan Lee
 * Contact: jonlee27@seas.upenn.edu
 */
#include "src/elevate_constants.h"
#include "src/elevate_module.h"
#include "src/button_panel.h"
#include "src/elevate_system.h"

ElevateModule module_0 = ElevateModule(
  PWM_PIN_0,
  PWM_CHANNEL_0,
  DIRECTION_PIN_0,
  ENCODER_PORT_0,
  UPPER_LIMIT_SWITCH_PIN_0,
  LOWER_LIMIT_SWITCH_PIN_0
);
// ElevateModule module_1 = ElevateModule(
//   PWM_PIN_1,
//   PWM_CHANNEL_1,
//   DIRECTION_PIN_1,
//   ENCODER_PORT_1,
//   UPPER_LIMIT_SWITCH_PIN_1,
//   LOWER_LIMIT_SWITCH_PIN_1
// );
// ElevateModule module_2 = ElevateModule(
//   PWM_PIN_2,
//   PWM_CHANNEL_2,
//   DIRECTION_PIN_2,
//   ENCODER_PORT_2,
//   UPPER_LIMIT_SWITCH_PIN_2,
//   LOWER_LIMIT_SWITCH_PIN_2
// );
// ElevateModule module_3 = ElevateModule(
//   PWM_PIN_3,
//   PWM_CHANNEL_3,
//   DIRECTION_PIN_3,
//   ENCODER_PORT_3,
//   UPPER_LIMIT_SWITCH_PIN_3,
//   LOWER_LIMIT_SWITCH_PIN_3
// );

int const NUMBER_OF_MODULES = 1;

ElevateModule modules[NUMBER_OF_MODULES] = {
  module_0
  // module_1,
  // module_2,
  // module_3
};

ButtonPanel button_panel = ButtonPanel(UP_SWITCH_PIN_, DOWN_SWITCH_PIN_);

ElevateSystem elevate = ElevateSystem(modules, NUMBER_OF_MODULES, &button_panel);

void setup() {
  Serial.begin(9600);
  elevate.setup();
}

void loop() {
  elevate.update();
  elevate.control();
}
