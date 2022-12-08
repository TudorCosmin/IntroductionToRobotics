#include "variables.h"
#include "functions.h"
#include "joystick_move.h"

#include "settings_menu.h"
#include "main_menu.h"

#include "core.h"
#include "game.h"

unsigned long timp = 0;

void setup() {
  Serial.begin(9600);
  initialization();
  
  // for(int i = 3; i < 125; i++)
  //   EEPROM.update(i, 0);
}

void loop() {
  buzzer.loop();
  inputData();
  changeState();
}