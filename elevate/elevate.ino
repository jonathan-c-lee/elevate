/**
 * @file elevate.ino
 * 
 * @brief main code for running elevate system
 * 
 * @author Jonathan Lee
 * Contact: jonlee27@seas.upenn.edu
 */
#include "elevate_module.h"
#include "button_panel.h"
#include "elevate_system.h"

#define PWM_PIN_0                4
#define PWM_CHANNEL_0            0
#define DIRECTION_PIN_0          5
#define ENCODER_PORT_0           5
#define UPPER_LIMIT_SWITCH_PIN_0 42
#define LOWER_LIMIT_SWITCH_PIN_0 41

#define PWM_PIN_1                4
#define PWM_CHANNEL_1            0
#define DIRECTION_PIN_1          5
#define ENCODER_PORT_1           4
#define UPPER_LIMIT_SWITCH_PIN_1 39
#define LOWER_LIMIT_SWITCH_PIN_1 38

#define PWM_PIN_2                4
#define PWM_CHANNEL_2            0
#define DIRECTION_PIN_2          5
#define ENCODER_PORT_2           3
#define UPPER_LIMIT_SWITCH_PIN_2 36
#define LOWER_LIMIT_SWITCH_PIN_2 35

#define PWM_PIN_3                4
#define PWM_CHANNEL_3            0
#define DIRECTION_PIN_3          5
#define ENCODER_PORT_3           2
#define UPPER_LIMIT_SWITCH_PIN_3 34
#define LOWER_LIMIT_SWITCH_PIN_3 33

#define UP_SWITCH_PIN   10
#define DOWN_SWITCH_PIN 18

int const NUMBER_OF_MODULES = 4;

ElevateModule module_0 = ElevateModule(
  PWM_PIN_0,
  PWM_CHANNEL_0,
  DIRECTION_PIN_0,
  ENCODER_PORT_0,
  UPPER_LIMIT_SWITCH_PIN_0,
  LOWER_LIMIT_SWITCH_PIN_0
);
ElevateModule module_1 = ElevateModule(
  PWM_PIN_1,
  PWM_CHANNEL_1,
  DIRECTION_PIN_1,
  ENCODER_PORT_1,
  UPPER_LIMIT_SWITCH_PIN_1,
  LOWER_LIMIT_SWITCH_PIN_1
);
ElevateModule module_2 = ElevateModule(
  PWM_PIN_2,
  PWM_CHANNEL_2,
  DIRECTION_PIN_2,
  ENCODER_PORT_2,
  UPPER_LIMIT_SWITCH_PIN_2,
  LOWER_LIMIT_SWITCH_PIN_2
);
ElevateModule module_3 = ElevateModule(
  PWM_PIN_3,
  PWM_CHANNEL_3,
  DIRECTION_PIN_3,
  ENCODER_PORT_3,
  UPPER_LIMIT_SWITCH_PIN_3,
  LOWER_LIMIT_SWITCH_PIN_3
);

ElevateModule modules[NUMBER_OF_MODULES] = {
  module_0,
  module_1,
  module_2,
  module_3
};

ButtonPanel button_panel = ButtonPanel(UP_SWITCH_PIN, DOWN_SWITCH_PIN);

ElevateSystem elevate = ElevateSystem(modules, NUMBER_OF_MODULES, &button_panel);

void setup() {
  elevate.setup();
}

void loop() {
  elevate.update();
  elevate.control();
}
