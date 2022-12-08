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


  // mapX = 3;
  // mapY = 3;
  // levels[currentLevel][playerX][playerY] = 1;
  // displayGame();
  // Serial.println(levels[0][0][0]);

  // for(int i = 3; i < 125; i++)
  //   EEPROM.update(i, 0);
}

void loop() {
  buzzer.loop();
  inputData();
  changeState();

  // if(isRunning) {
  //   run();
  // }
  // else {
  //   changeState();
  // }

  // if (buzzer.getState() == BUZZER_IDLE) {
  // if(millis() % 1000 == 0)
  //   buzzer.playMelody(melody, noteDurations, 1);
  // if(millis() % 1000 == 50)
  //   buzzer.stop();
  // }
  

  // tone(buzzerPin, 1000);
  

  // exemple: tre sa ma uit in menu.h

  // lcd.setCursor(0, 0);
  // lcd.print("printez ceva");
  // analogWrite(lcdBrightnessPin, lcdBrightness);
  // lcdContrast = 255;
  // for(int i = 0; i < 256; i = (i + 10) % 256) {
  //   analogWrite(lcdContrastPin, 0.3);
  //   Serial.println(i);

  //   delay(100);
  // }
  // tone(buzzerPin, 600);
}