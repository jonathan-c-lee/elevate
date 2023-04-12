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
 * id:    minion ID
 * angle: angle reading
 */
struct MinionMessage {
  unsigned int id;
  int angle;
};
MinionMessage message;

ElevateModule module_0 = ElevateModule(
  PWM_PIN_0,
  PWM_CHANNEL_0,
  DIRECTION_PIN_0,
  UPPER_LIMIT_SWITCH_PIN_0,
  LOWER_LIMIT_SWITCH_PIN_0
);
// ElevateModule module_1 = ElevateModule(
//   PWM_PIN_1,
//   PWM_CHANNEL_1,
//   DIRECTION_PIN_1,
//   UPPER_LIMIT_SWITCH_PIN_1,
//   LOWER_LIMIT_SWITCH_PIN_1
// );
// ElevateModule module_2 = ElevateModule(
//   PWM_PIN_2,
//   PWM_CHANNEL_2,
//   DIRECTION_PIN_2,
//   UPPER_LIMIT_SWITCH_PIN_2,
//   LOWER_LIMIT_SWITCH_PIN_2
// );
// ElevateModule module_3 = ElevateModule(
//   PWM_PIN_3,
//   PWM_CHANNEL_3,
//   DIRECTION_PIN_3,
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

/**
 * Callback when data is received from minion
 */
void receive_callback(const uint8_t* mac_address, const uint8_t* data, int len) {
  memcpy(&message, data, sizeof(message));
  modules[message.id].update_height(message.angle);
}

void setup() {
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) return;
  esp_now_register_recv_cb(receive_callback);
  elevate.setup();
}

void loop() {
  elevate.update();
  elevate.control();
}
