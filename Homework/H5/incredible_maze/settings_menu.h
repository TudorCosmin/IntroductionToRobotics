#ifndef SETTINHGS_MENU_H
#define SETTINGS_MENU_H

void settingsMenu() {
   if(currentItem != maxCurrentItem) {
    lcd.setCursor(0, 0);
    lcd.write(arrowRightCode);

    lcd.setCursor(1, 0);
    lcd.print(settingsMenuItems[currentItem]);

    lcd.setCursor(1, 1);
    lcd.print(settingsMenuItems[currentItem + 1]);
  }
  else {
    lcd.setCursor(0, 1);
    lcd.write(arrowRightCode);

    lcd.setCursor(1, 0);
    lcd.print(settingsMenuItems[currentItem - 1]);

    lcd.setCursor(1, 1);
    lcd.print(settingsMenuItems[currentItem]);
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
      gameState = enterNameGS;
    }
    else if (currentItem == 1) {
      gameState = selectLevelGS;
    }
    else if (currentItem == 2) {
      gameState = lcdBrightnessGS;
    }
    else if (currentItem == 3) {
      displayImage(images[5]);
      gameState = matrixBrightnessGS;
    }
    else if (currentItem == 4) {
      gameState = selectSoundGS;
    }
    else if (currentItem == 5) {
      gameState = initialGS;
      maxCurrentItem = 4;
    }

    if(currentItem == 5) {
      currentItem = 2;
    }
    buttonPressed = false;
    lcd.clear();
  }

  if(changedMenuItem)
    lcd.clear();
}

void enterNameMenu() {
  lcd.setCursor(0, 0);
  lcd.print("Index:");
  lcd.setCursor(0, 1);
  lcd.print("Letter:");

  lcd.setCursor(8 + selectNamePos, 0);
  lcd.write(arrowDownCode);

  lcd.setCursor(8, 1);
  lcd.print(currentName[0]);
  lcd.setCursor(9, 1);
  lcd.print(currentName[1]);
  lcd.setCursor(10, 1);
  lcd.print(currentName[2]);
  lcd.setCursor(11, 1);
  lcd.print(currentName[3]);

  lcd.setCursor(14, 0);
  lcd.write(arrowLeftCode);
  lcd.setCursor(15, 0);
  lcd.write(arrowRightCode);
  lcd.setCursor(14, 1);
  lcd.write(arrowDownCode);
  lcd.setCursor(15, 1);
  lcd.write(arrowUpCode);

  if(up) {
    currentName[selectNamePos] = min(currentName[selectNamePos] + 1, 'Z');
    up = false;
  }

  if(down) {
    currentName[selectNamePos] = max(currentName[selectNamePos] - 1, 'A');
    down = false;
  }

  if(left) {
    lcd.setCursor(8 + selectNamePos, 0);
    lcd.write(' ');
    selectNamePos = max(0, selectNamePos - 1);
    left = false;
  }

  if(right) {
    lcd.setCursor(8 + selectNamePos, 0);
    lcd.write(' ');
    selectNamePos = min(3, selectNamePos + 1);
    right = false;
  }

  if(buttonPressed) {
    gameState = settingsGS;
    buttonPressed = false;
    lcd.clear();
  }
}

void selectLevelMenu() {
  lcd.setCursor(0, 0);
  lcd.write(arrowRightCode);

  lcd.setCursor(1, 0);
  lcd.print("Level");

  lcd.setCursor(9, 0);
  lcd.write(arrowLeftCode);

  lcd.setCursor(10, 0);
  lcd.print((char)(48 + currentLevel));

  lcd.setCursor(11, 0);
  lcd.write(arrowRightCode);

  lcd.setCursor(1, 1);
  lcd.print(settingsMenuItems[2]);

  if(left && currentLevel != 0) {
      currentLevel--;
      settingsMenuItems[1][9] = (char)(48 + currentLevel);
      left = false;
    }
    if(right && currentLevel != maxLevel) {
      currentLevel++;
      settingsMenuItems[1][9] = (char)(48 + currentLevel);
      right = false;
    }

  if(buttonPressed) {
    gameState = settingsGS;
    buttonPressed = false;
    lcd.clear();
  }
}

void lcdBrightnessMenu() {
  lcd.setCursor(1, 0);
  lcd.print("Set brightness");

  lcd.setCursor(0, 1);
  lcd.print("[");

  lcd.setCursor(15, 1);
  lcd.print("]");

  for(int i = 2; i <= 15; i++) {
    lcd.setCursor(i - 1, 1);
    if(i <= map(lcdBrightness, 20, 255, 2, 15))
      lcd.write(slidingBarCode);
    else lcd.write(' ');
  }

  if(left) {
    lcdBrightness = max(lcdBrightness - 60, 1);
    analogWrite(lcdBrightnessPin, lcdBrightness);
    left = false;
  }
  if(right) {
    lcdBrightness = min(lcdBrightness + 60, 255);
    analogWrite(lcdBrightnessPin, lcdBrightness);
    right = false;
  }

  if(buttonPressed) {
    EEPROM.update(lcdBrightnessAddress, lcdBrightness);
    gameState = settingsGS;
    buttonPressed = false;
    lcd.clear();
  }
}

void matrixBrightnessMenu() {
  lcd.setCursor(1, 0);
  lcd.print("Set brightness");

  lcd.setCursor(0, 1);
  lcd.print("[");

  lcd.setCursor(15, 1);
  lcd.print("]");

  for(int i = 2; i <= 15; i++) {
    lcd.setCursor(i - 1, 1);
    if(i <= matrixBrightness)
      lcd.write(slidingBarCode);
    else lcd.write(' ');
  }

  if(left) {
    matrixBrightness = max(matrixBrightness - 3, 1);
    matrix.setIntensity(0, matrixBrightness);
    left = false;
  }
  if(right) {
    matrixBrightness = min(matrixBrightness + 3, 15);
    matrix.setIntensity(0, matrixBrightness);
    right = false;
  }

  if(buttonPressed) {
    EEPROM.update(matrixBrightnessAddress, matrixBrightness);
    gameState = settingsGS;
    buttonPressed = false;
    matrix.clearDisplay(0);
    lcd.clear();
  }
}

void selectSoundMenu() {
  lcd.setCursor(0, 0);
  lcd.write(arrowRightCode);

  lcd.setCursor(1, 0);
  lcd.print("Sound");

  lcd.setCursor(9, 0);
  lcd.write(arrowLeftCode);

  lcd.setCursor(10, 0);
  if(soundOn) {
    lcd.print("Y");
  }
  else {
    lcd.print("N");
  }

  lcd.setCursor(11, 0);
  lcd.write(arrowRightCode);

  lcd.setCursor(1, 1);
  lcd.print(settingsMenuItems[5]);

  if(left || right) {
    if(soundOn) {
      settingsMenuItems[4][9] = 'N';
      soundOn = false;
    }
    else {
      settingsMenuItems[4][9] = 'Y';
      soundOn = true;
    }
    left = right = false;
  }

  if(buttonPressed) {
    EEPROM.update(soundAddress, soundOn);
    gameState = settingsGS;
    buttonPressed = false;
    lcd.clear();
  }
}

#endif