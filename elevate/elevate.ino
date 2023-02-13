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

#define UP_PWM_PIN_0             0
#define UP_PWM_CHANNEL_0         0
#define DOWN_PWM_PIN_0           0
#define DOWN_PWM_CHANNEL_0       0
#define ENCODER_PORT_0           0
#define UPPER_LIMIT_SWITCH_PIN_0 0
#define LOWER_LIMIT_SWITCH_PIN_0 0

#define UP_PWM_PIN_1             0
#define UP_PWM_CHANNEL_1         0
#define DOWN_PWM_PIN_1           0
#define DOWN_PWM_CHANNEL_1       0
#define ENCODER_PORT_1           0
#define UPPER_LIMIT_SWITCH_PIN_1 0
#define LOWER_LIMIT_SWITCH_PIN_1 0

#define UP_PWM_PIN_2             0
#define UP_PWM_CHANNEL_2         0
#define DOWN_PWM_PIN_2           0
#define DOWN_PWM_CHANNEL_2       0
#define ENCODER_PORT_2           0
#define UPPER_LIMIT_SWITCH_PIN_2 0
#define LOWER_LIMIT_SWITCH_PIN_2 0

#define UP_PWM_PIN_3             0
#define UP_PWM_CHANNEL_3         0
#define DOWN_PWM_PIN_3           0
#define DOWN_PWM_CHANNEL_3       0
#define ENCODER_PORT_3           0
#define UPPER_LIMIT_SWITCH_PIN_3 0
#define LOWER_LIMIT_SWITCH_PIN_3 0

#define UP_SWITCH_PIN   0
#define DOWN_SWITCH_PIN 0

int const NUMBER_OF_MODULES = 4;

ElevateModule module_0 = ElevateModule(
  UP_PWM_PIN_0,
  UP_PWM_CHANNEL_0,
  DOWN_PWM_PIN_0,
  DOWN_PWM_CHANNEL_0,
  ENCODER_PORT_0,
  UPPER_LIMIT_SWITCH_PIN_0,
  LOWER_LIMIT_SWITCH_PIN_0
);
ElevateModule module_1 = ElevateModule(
  UP_PWM_PIN_1,
  UP_PWM_CHANNEL_1,
  DOWN_PWM_PIN_1,
  DOWN_PWM_CHANNEL_1,
  ENCODER_PORT_1,
  UPPER_LIMIT_SWITCH_PIN_1,
  LOWER_LIMIT_SWITCH_PIN_1
);
ElevateModule module_2 = ElevateModule(
  UP_PWM_PIN_2,
  UP_PWM_CHANNEL_2,
  DOWN_PWM_PIN_2,
  DOWN_PWM_CHANNEL_2,
  ENCODER_PORT_2,
  UPPER_LIMIT_SWITCH_PIN_2,
  LOWER_LIMIT_SWITCH_PIN_2
);
ElevateModule module_3 = ElevateModule(
  UP_PWM_PIN_3,
  UP_PWM_CHANNEL_3,
  DOWN_PWM_PIN_3,
  DOWN_PWM_CHANNEL_3,
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
