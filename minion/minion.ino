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
#include "src/encoder.h"

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

// ESP-NOW parameters
esp_now_peer_info_t const master = {
  .peer_addr = {0xF4, 0x12, 0xFA, 0x42, 0x09, 0x54},
  .channel = 0,
  .encrypt = false,
};

Encoder const encoder = Encoder();

void setup() {
  // communication setup
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) return;
  if (esp_now_add_peer(&master) != ESP_OK) return;

  message.id = 0;
}

void loop() {
  message.angle = encoder.get_raw_angle();
  esp_now_send(master.peer_addr, (uint8_t *) &message, sizeof(message));
  delay(15);
}
