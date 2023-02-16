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

// #define UP_PWM_PIN_0             4
// #define UP_PWM_CHANNEL_0         0
// #define DOWN_PWM_PIN_0           5
// #define DOWN_PWM_CHANNEL_0       1
// #define ENCODER_PORT_0           5
// #define UPPER_LIMIT_SWITCH_PIN_0 42
// #define LOWER_LIMIT_SWITCH_PIN_0 41

// #define UP_PWM_PIN_1             15
// #define UP_PWM_CHANNEL_1         2
// #define DOWN_PWM_PIN_1           16
// #define DOWN_PWM_CHANNEL_1       3
// #define ENCODER_PORT_1           4
// #define UPPER_LIMIT_SWITCH_PIN_1 39
// #define LOWER_LIMIT_SWITCH_PIN_1 38

// #define UP_PWM_PIN_2             9
// #define UP_PWM_CHANNEL_2         4
// #define DOWN_PWM_PIN_2           10
// #define DOWN_PWM_CHANNEL_2       5
// #define ENCODER_PORT_2           3
// #define UPPER_LIMIT_SWITCH_PIN_2 36
// #define LOWER_LIMIT_SWITCH_PIN_2 35

// #define UP_PWM_PIN_3             13
// #define UP_PWM_CHANNEL_3         6
// #define DOWN_PWM_PIN_3           14
// #define DOWN_PWM_CHANNEL_3       7
// #define ENCODER_PORT_3           2
// #define UPPER_LIMIT_SWITCH_PIN_3 34
// #define LOWER_LIMIT_SWITCH_PIN_3 33

#define UP_SWITCH_PIN   10
#define DOWN_SWITCH_PIN 18

// int const NUMBER_OF_MODULES = 4;

// ElevateModule module_0 = ElevateModule(
//   UP_PWM_PIN_0,
//   UP_PWM_CHANNEL_0,
//   DOWN_PWM_PIN_0,
//   DOWN_PWM_CHANNEL_0,
//   ENCODER_PORT_0,
//   UPPER_LIMIT_SWITCH_PIN_0,
//   LOWER_LIMIT_SWITCH_PIN_0
// );
// ElevateModule module_1 = ElevateModule(
//   UP_PWM_PIN_1,
//   UP_PWM_CHANNEL_1,
//   DOWN_PWM_PIN_1,
//   DOWN_PWM_CHANNEL_1,
//   ENCODER_PORT_1,
//   UPPER_LIMIT_SWITCH_PIN_1,
//   LOWER_LIMIT_SWITCH_PIN_1
// );
// ElevateModule module_2 = ElevateModule(
//   UP_PWM_PIN_2,
//   UP_PWM_CHANNEL_2,
//   DOWN_PWM_PIN_2,
//   DOWN_PWM_CHANNEL_2,
//   ENCODER_PORT_2,
//   UPPER_LIMIT_SWITCH_PIN_2,
//   LOWER_LIMIT_SWITCH_PIN_2
// );
// ElevateModule module_3 = ElevateModule(
//   UP_PWM_PIN_3,
//   UP_PWM_CHANNEL_3,
//   DOWN_PWM_PIN_3,
//   DOWN_PWM_CHANNEL_3,
//   ENCODER_PORT_3,
//   UPPER_LIMIT_SWITCH_PIN_3,
//   LOWER_LIMIT_SWITCH_PIN_3
// );

// ElevateModule modules[NUMBER_OF_MODULES] = {
//   module_0,
//   module_1,
//   module_2,
//   module_3
// };

ButtonPanel button_panel = ButtonPanel(UP_SWITCH_PIN, DOWN_SWITCH_PIN);

bool up_pressed = false;
int count = 0;
bool down_pressed = false;


// ElevateSystem elevate = ElevateSystem(modules, NUMBER_OF_MODULES, &button_panel);

void setup() {
  Serial.begin(115200);
  button_panel.setup();
}

void loop() {
  if (button_panel.up_switch_pressed()) {
    if (!up_pressed) {
      up_pressed = true;
      Serial.println("UP PRESSED");
      Serial.println(count);
      count = 0;
    }
  } else {
    if (up_pressed) {
      up_pressed = false;
      Serial.println("UP RELEASED");
    }
  }
  if (button_panel.down_switch_pressed()) {
    if (!down_pressed) {
      down_pressed = true;
      Serial.println("DOWN PRESSED");
      count++;
    }
  } else {
    if (down_pressed) {
      down_pressed = false;
      Serial.println("DOWN RELEASED");
    }
  }

  // elevate.update();
  // elevate.control();
}
