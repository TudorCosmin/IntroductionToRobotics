#ifndef MAIN_MENU_H
#define MAIN_MENU_H

void mainMenu() {
  displayImage(images[currentItem]);

  if(currentItem != maxCurrentItem) {
    lcd.setCursor(0, 0);
    lcd.write(arrowRightCode);

    lcd.setCursor(1, 0);
    lcd.print(mainMenuItems[currentItem]);

    lcd.setCursor(1, 1);
    lcd.print(mainMenuItems[currentItem + 1]);
  }
  else {
    lcd.setCursor(0, 1);
    lcd.write(arrowRightCode);

    lcd.setCursor(1, 0);
    lcd.print(mainMenuItems[currentItem - 1]);

    lcd.setCursor(1, 1);
    lcd.print(mainMenuItems[currentItem]);
  }
  menuArrows();

  
  changedMenuItem = false;
  if(up) {
    if(currentItem != minCurrentItem) {
      changedMenuItem = true;
      beepBuzz(yepBeep);
    }
    else {
      beepBuzz(nopeBeep);
    }
    currentItem = max(currentItem - 1, minCurrentItem);
    up = false;
  }
  if(down) {
    if(currentItem != maxCurrentItem) {
      changedMenuItem = true;
      beepBuzz(yepBeep);
    }
    else {
      beepBuzz(nopeBeep);
    }
    currentItem = min(currentItem + 1, maxCurrentItem);
    down = false;
  }

  if(buttonPressed) {
    if (currentItem == 0) {
      gameState = runGS;
      startGameTime = millis();

      // int length = sizeof(noteDurations) / sizeof(int);
      // buzzer.playMelody(melody, noteDurations, length);
      // ------------------------------- play a song maybe?
    }
    else if (currentItem == 1) {
      gameState = highscoreGS;
    }
    else if (currentItem == 2) {
      gameState = settingsGS;
      maxCurrentItem = 5;
    }
    else if (currentItem == 3) {
      gameState = creditsGS;
    }
    else if (currentItem == 4) {
      gameState = howToPlayGS;
    }
    if(currentItem == 2)
      currentItem = 0;
    buttonPressed = false;
    lcd.clear();
  }

  if(changedMenuItem)
    lcd.clear();
}

void highscoreMenu() {
  lcd.setCursor(2, 0);
  lcd.print("Best level ");
  lcd.setCursor(13, 0);
  lcd.print(highscoreLevel);

  lcd.setCursor(0, 0);
  lcd.write(arrowLeftCode);
  lcd.setCursor(15, 0);
  lcd.write(arrowRightCode);
  lcd.setCursor(14, 1);
  lcd.write(arrowDownCode);
  lcd.setCursor(15, 1);
  lcd.write(arrowUpCode);

  lcd.setCursor(0, 1);
  lcd.print(highscorePosition);
  lcd.setCursor(1, 1);
  lcd.print(".");

  static int currentLevelStartAddress, currentPositionStartAddress;
  currentLevelStartAddress = 3 + highscoreLevel * 25;
  currentPositionStartAddress = currentLevelStartAddress + 5 * (highscorePosition - 1);
  // Serial.println(currentLevelStartAddress);
  // Serial.println(currentPositionStartAddress);
  // Serial.println(currentLevelStartAddress + 5 * (highscorePosition - 1));
  // Serial.println();

  if(EEPROM.read(currentPositionStartAddress) == 0) {
    lcd.setCursor(2, 1);
    // lcd.print("---- ---sec");
    lcd.print(" no player ");
  }
  else {
    lcd.setCursor(6, 1);
    lcd.print(' ');
    lcd.setCursor(9, 1);
    lcd.print(' ');

    lcd.setCursor(2, 1);
    lcd.print((char)EEPROM.read(currentPositionStartAddress));
    lcd.setCursor(3, 1);
    lcd.print((char)EEPROM.read(currentPositionStartAddress + 1));
    lcd.setCursor(4, 1);
    lcd.print((char)EEPROM.read(currentPositionStartAddress + 2));
    lcd.setCursor(5, 1);
    lcd.print((char)EEPROM.read(currentPositionStartAddress + 3));
    lcd.setCursor(7, 1);
    lcd.print((int)EEPROM.read(currentPositionStartAddress + 4));
    lcd.setCursor(10, 1);
    lcd.print("sec");
  }

  if(up) {
    highscorePosition = max(1, highscorePosition - 1);
    up = false;
  }
  if(down) {
    highscorePosition = min(5, highscorePosition + 1);
    down = false;
  }
  if(left) {
    highscoreLevel = max(0, highscoreLevel - 1);
    left = false;
  }
  if(right) {
    highscoreLevel = min(maxLevel, highscoreLevel + 1);
    right = false;
  }

  if(buttonPressed) {
    gameState = initialGS;
    buttonPressed = false;
    lcd.clear();
  }
}

void creditsMenu() {
  if(resetInfoStartTime) {
    infoStartTime = millis();
    startLetter = 0;
    resetInfoStartTime = false;
  }

  lcd.setCursor(4, 0);
  lcd.print("Credits:");

  if((millis() - infoStartTime) % 250 < 10) {
    Serial.println(startLetter);
    lcd.setCursor(0, 1);
    for (int i = startLetter; i <= startLetter + 15; i++) {
      lcd.print(creditsMessage[i]);
    }
    startLetter++;
    if(startLetter == strlen(creditsMessage) - 15) {
      startLetter = 0;
    }
  }

  if(buttonPressed) {
    gameState = initialGS;
    resetInfoStartTime = true;
    buttonPressed = false;
    lcd.clear();
  }
}

void howToPlayMenu() {
  if(resetInfoStartTime) {
    infoStartTime = millis();
    startLetter = 0;
    resetInfoStartTime = false;
  }

  lcd.setCursor(2, 0);
  lcd.print("How to play:");

  if((millis() - infoStartTime) % 250 < 10) {
    Serial.println(startLetter);
    lcd.setCursor(0, 1);
    for (int i = startLetter; i <= startLetter + 15; i++) {
      lcd.print(howToPlayMessage[i]);
    }
    startLetter++;
    if(startLetter == strlen(howToPlayMessage) - 15) {
      startLetter = 0;
    }
  }

  if(buttonPressed) {
    gameState = initialGS;
    resetInfoStartTime = true;
    buttonPressed = false;
    lcd.clear();
  }
}

#endif