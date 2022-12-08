#ifndef GAME_H
#define GAME_H

void run() {
  elapsedTime = millis() - startGameTime;
  movePlayer();
  blinkPlayer();
  displayGame();
  printScore();

  if(win) {
    win = false;
    gameState = endGameGS;
    lcd.clear();
  }
}

void endGame() {
  // aici ar trebui sa afisez si ceva pe matrice

  lcd.setCursor(0, 0);
  lcd.print("Congrats,     !");
  lcd.setCursor(10, 0);
  lcd.print(currentName[0]);
  lcd.setCursor(11, 0);
  lcd.print(currentName[1]);
  lcd.setCursor(12, 0);
  lcd.print(currentName[2]);
  lcd.setCursor(13, 0);
  lcd.print(currentName[3]);
  
  lcd.setCursor(0, 1);
  lcd.print("Time: ");

  lcd.setCursor(6, 1);
  lcd.print(elapsedTime / 1000);

  lcd.setCursor(12, 1);
  lcd.print("LVL");
  lcd.setCursor(15, 1);
  lcd.print(currentLevel);

  if(buttonPressed) { // aici ar trebui sa ma duc la next level
    saveScore();
    levels[currentLevel][playerX][playerY] = 0;
    mapX = 0;
    mapY = 0;
    playerX = 1;
    playerY = 1;

    gameState = initialGS;
    buttonPressed = false;
    lcd.clear();
  }
}

void saveScore() {
  // EEPROM.put(3, currentName);
  // EEPROM.update(3 + sizeof(currentName), elapsedTime / 1000);

  // EEPROM.put(3 + sizeof(currentName) + 1, currentName);
  // EEPROM.update(3 + sizeof(currentName) + 1 + sizeof(currentName), 555);

  static int i, j, score, currentsCore, currentLevelStartAddress;
  currentLevelStartAddress = 3 + currentLevel * 25;
  currentsCore = elapsedTime / 1000;
  for(i = 1; i <= 5; i++) {
    score = EEPROM.read(currentLevelStartAddress + 5 * i - 1);
    if(score == 0 || currentsCore < score) {
      for(j = currentLevelStartAddress + 24; j > 5 * i - 1; j--) {
        EEPROM.update(j, EEPROM.read(j - 5));
      }

      EEPROM.update(currentLevelStartAddress + 5 * (i - 1), currentName[0]);
      EEPROM.update(currentLevelStartAddress + 5 * (i - 1) + 1, currentName[1]);
      EEPROM.update(currentLevelStartAddress + 5 * (i - 1) + 2, currentName[2]);
      EEPROM.update(currentLevelStartAddress + 5 * (i - 1) + 3, currentName[3]);
      EEPROM.update(currentLevelStartAddress + 5 * (i - 1) + 4, currentsCore);
      i = 6;
    }
  }
}

bool legalMove(int i, int j) {
  return i > 0 && j > 0 && i < 16 && j < 16 && levels[currentLevel][i][j] != 1;
}

void movePlayer() {
  if(up) {
    if(legalMove(playerX - 1, playerY)) {
      levels[currentLevel][playerX][playerY] = 0;
      playerX--;
      levels[currentLevel][playerX][playerY] = 1;

      if(mapX > 0 && playerX < mapX + border) {
        mapX--;
      }

      beepBuzz(yepBeep);
    }
    else {
      beepBuzz(nopeBeep);
    }
    up = false;
  }

  if(down) {
    if(legalMove(playerX + 1, playerY)) {
      levels[currentLevel][playerX][playerY] = 0;
      playerX++;
      levels[currentLevel][playerX][playerY] = 1;

      if(mapX < 8 && playerX > mapX - border) {
        mapX++;
      }
      
      beepBuzz(yepBeep);
    }
    else {
      beepBuzz(nopeBeep);
    }
    down = false;
  }

  if(left) {
    if(legalMove(playerX, playerY - 1)) {
      levels[currentLevel][playerX][playerY] = 0;
      playerY--;
      levels[currentLevel][playerX][playerY] = 1;

      if(mapY > 0 && playerY < mapY + border) {
        mapY--;
      }
      
      beepBuzz(yepBeep);
    }
    else {
      beepBuzz(nopeBeep);
    }
    left = false;
  }

  if(right) {
    if(legalMove(playerX, playerY + 1)) {
      levels[currentLevel][playerX][playerY] = 0;
      playerY++;
      levels[currentLevel][playerX][playerY] = 1;

      if(mapY < 8 && playerY > mapY - border) {
        mapY++;
      }
      
      beepBuzz(yepBeep);
    }
    else {
      beepBuzz(nopeBeep);
    }
    right = false;
  }

  if(playerX == mapSize && playerY == mapSize) {
    win = true;
  }
}

void blinkPlayer() {
  if(!win && elapsedTime % 50 < 5) {
    levels[currentLevel][playerX][playerY] = !levels[currentLevel][playerX][playerY];
  }
}

void printScore() {
  lcd.setCursor(0, 0);
  lcd.print("Move fast,     !");

  lcd.setCursor(11, 0);
  lcd.print(currentName);

  lcd.setCursor(0, 1);
  lcd.print("Time: ");

  lcd.setCursor(6, 1);
  lcd.print(elapsedTime / 1000);

  lcd.setCursor(12, 1);
  lcd.print("LVL");
  lcd.setCursor(15, 1);
  lcd.print(currentLevel);
}

#endif