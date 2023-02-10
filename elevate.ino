/**
 * @file elevate.ino
 * 
 * @brief main code for running elevate system
 * 
 * @author Jonathan Lee
 * Contact: jonlee27@seas.upenn.edu
 */
#include "elevate_types.h"
#include "switch_utility.h"
#include "elevate_module.h"
#include "button_panel.h"
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

#define UP_SWITCH_PIN   0
#define DOWN_SWITCH_PIN 0

uint8_t const NUMBER_OF_MODULES = 4;

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

  // create button panel
  ButtonPanel const button_panel = ButtonPanel(UP_SWITCH_PIN, DOWN_SWITCH_PIN);

  // create elevate system
  ElevateSystem elevate = ElevateSystem(modules, NUMBER_OF_MODULES, &button_panel);
}

void loop() {
  elevate.update_module_status();
  elevate.update_system_state();

  // elevate system moves based on state
  elevate.control();
}
