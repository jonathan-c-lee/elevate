/**
 * @file button_panel.cpp
 * 
 * @brief header file for button panel
 * 
 * @author Jonathan Lee
 * Contact: jonlee27@seas.upenn.edu
 */
#ifndef BUTTON_PANEL_H_
#define BUTTON_PANEL_H_

#include <arduino.h>

class ButtonPanel {
  public:
    ButtonPanel(uint8_t up_switch_pin, uint8_t down_switch_pin);
    void setup() const;
    bool up_switch_pressed() const;
    bool down_switch_pressed() const;

  private:
    uint8_t const UP_SWITCH_PIN;
    uint8_t const DOWN_SWITCH_PIN;
};

#endif
