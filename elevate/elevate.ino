/**
 * @file elevate.ino
 * 
 * @brief main code for running elevate system
 * 
 * @author Jonathan Lee
 * Contact: jonlee27@seas.upenn.edu
 */
#include <WiFi.h>
#include <esp_now.h>
#include "src/elevate_constants.h"
#include "src/elevate_module.h"
#include "src/button_panel.h"
#include "src/elevate_system.h"

/**
 * Struct for messages from encoder minion
 * 
 * id:                         minion ID
 * height:                     module height
 * lower_limit_switch_pressed: whether or not the lower limit switch is pressed
 * upper_limit_switch_pressed: whether or not the upper limit switch is pressed
 */
struct MinionMessage {
  unsigned int id;
  int height;
  bool lower_limit_switch_pressed;
  bool upper_limit_switch_pressed;
};
MinionMessage message;

ElevateModule module_0 = ElevateModule(
  PWM_PIN_0,
  PWM_CHANNEL_0,
  DIRECTION_PIN_0
);
// ElevateModule module_1 = ElevateModule(
//   PWM_PIN_1,
//   PWM_CHANNEL_1,
//   DIRECTION_PIN_1
// );
// ElevateModule module_2 = ElevateModule(
//   PWM_PIN_2,
//   PWM_CHANNEL_2,
//   DIRECTION_PIN_2
// );
// ElevateModule module_3 = ElevateModule(
//   PWM_PIN_3,
//   PWM_CHANNEL_3,
//   DIRECTION_PIN_3
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

/**
 * Callback when data is received from minion
 */
void receive_callback(const uint8_t* mac_address, const uint8_t* data, int len) {
  memcpy(&message, data, sizeof(message));
  modules[message.id].update(
    message.height,
    message.lower_limit_switch_pressed,
    message.upper_limit_switch_pressed
  );
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.setSleep(false);
  if (esp_now_init() != ESP_OK) return;
  esp_now_register_recv_cb(receive_callback);
  elevate.setup();
}

void loop() {
  elevate.update();
  elevate.control();
}
