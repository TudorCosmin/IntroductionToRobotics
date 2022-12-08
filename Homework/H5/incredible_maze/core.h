#ifndef CORE_H
#define CORE_H

void initialization() {
  lcdBrightness = EEPROM.read(lcdBrightnessAddress);
  matrixBrightness = EEPROM.read(matrixBrightnessAddress);
  soundOn = EEPROM.read(soundAddress);  

  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(lcdBrightnessPin, OUTPUT);

  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.createChar(arrowUpCode, arrowUpChar);
  lcd.createChar(arrowDownCode, arrowDownChar);
  lcd.createChar(arrowLeftCode, arrowLeftChar);
  lcd.createChar(arrowRightCode, arrowRightChar);
  lcd.createChar(slidingBarCode, slidingBarChar);
  
  matrix.shutdown(0, false);
  matrix.setIntensity(0, matrixBrightness); // sets brightness (0~15 possible values)
  matrix.clearDisplay(0);

  analogWrite(lcdBrightnessPin, lcdBrightness);

  // tone(buzzerPin, 0);

  gameState = initialGS;

  if(soundOn) {
      settingsMenuItems[4][9] = 'Y';
    }
    else {
      settingsMenuItems[4][9] = 'N';
    }

    
  levels[currentLevel][playerX][playerY] = 1;
}

void changeState() {
  analogWrite(lcdBrightnessPin, lcdBrightness); // ----------------- TREBUIE SA VAD CE E CU LINIA ASTA ????

  if(gameState == initialGS) {
    mainMenu();
  }
  else if(gameState == runGS) {
    run();
  }
  else if(gameState == endGameGS) {
    endGame();
  }
  else if(gameState == highscoreGS) {
    displayImage(images[1]);
    highscoreMenu();
  }
  else if(gameState == settingsGS) {
    displayImage(images[2]);
    settingsMenu();
  }
  else if(gameState == creditsGS) {
    displayImage(images[3]);
    creditsMenu();
  }
  else if(gameState == howToPlayGS) {
    displayImage(images[4]);
    howToPlayMenu();
  }
  else if(gameState == enterNameGS) {
    enterNameMenu();
  }
  else if(gameState == selectLevelGS) {
    selectLevelMenu();
  }
  else if(gameState == lcdBrightnessGS) {
    lcdBrightnessMenu();
  }
  else if(gameState == matrixBrightnessGS) {
    matrixBrightnessMenu();
  }
  else if(gameState == selectSoundGS) {
    selectSoundMenu();
  }
}

void menuArrows() {
  if(currentItem == minCurrentItem) {
    lcd.setCursor(15, 1);
    lcd.write(arrowDownCode);
  }
  else if(currentItem == maxCurrentItem) {
      lcd.setCursor(15, 0);
      lcd.write(arrowUpCode);
  }
  else {
    lcd.setCursor(15, 0);
    lcd.write(arrowUpCode);
    lcd.setCursor(15, 1);
    lcd.write(arrowDownCode);
  }
}

void displayImage(uint64_t image) {
  for (int i = 0; i < 8; i++) {
    byte row = (image >> i * 8) & 0xFF;
    for (int j = 0; j < 8; j++) {
      matrix.setLed(0, i, j, bitRead(row, j));
    }
  }
}

void displayGame() {
  static int i, j, x, y, value;

  for(i = 0; i < 8; i++) {
    for(j = 0; j < 8; j++) {
      x = mapX + i;
      y = mapY + j;
      value = levels[currentLevel][x][y];
      matrix.setLed(0, i, j, value);
    }
  }
}

void beepBuzz(int *beepType) {
  if(soundOn) {
    buzzer.playMelody(beepType, beepDuration, 1);
  }
}

#endif