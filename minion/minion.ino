// /**
//  * @file minion.ino
//  * 
//  * @brief main code for elevate encoder minion
//  * 
//  * @author Jonathan Lee
//  * Contact: jonlee27@seas.upenn.edu
//  */
#include <WiFi.h>
#include <esp_now.h>
#include "src/minion_constants.h"
#include "src/elevate_minion.h"

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

// ESP-NOW parameters
esp_now_peer_info_t const master = {
  .peer_addr = {0xF4, 0x12, 0xFA, 0x42, 0x09, 0x54},
  .channel = 1,
  .encrypt = false,
};

ElevateMinion minion = ElevateMinion(LOWER_LIMIT_SWITCH_PIN_0, UPPER_LIMIT_SWITCH_PIN_0);
unsigned long start;

void setup() {
  // communication setup
  WiFi.mode(WIFI_STA);
  WiFi.setSleep(false);
  if (esp_now_init() != ESP_OK) return;
  if (esp_now_add_peer(&master) != ESP_OK) return;

  minion.setup();
  message.id = 0;
}

void loop() {
  message.height = minion.update_height();
  message.lower_limit_switch_pressed = minion.lower_limit_switch_pressed();
  message.upper_limit_switch_pressed = minion.upper_limit_switch_pressed();
  esp_now_send(master.peer_addr, (uint8_t *) &message, sizeof(message));
  delay(20);
}
