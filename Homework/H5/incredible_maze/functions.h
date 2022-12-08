#ifndef FUNCTIONS_H
#define FUNCTIONS_H

// joystick_move.h
void inputData();

// settings_menu.h
void settingsMenu();
void enterNameMenu();
void selectLevelMenu();
void lcdBrightnessMenu();
void matrixBrightnessMenu();
void selectSoundMenu();

// main_menu.h
void mainMenu();
void highscoreMenu(); // doar niste text din eeprom
void creditsMenu(); // doar niste text
void howToPlayMenu(); // doar niste text

// core.h
void changeState();
void menuArrows();
void displayImage(uint64_t image);
void displayGame();
void beepBuzz(int *beepType);

// game.h
void run();
void endGame();
void saveScore();
void movePlayer();
bool legalMove(byte i, byte j);
void blinkPlayer();
void printScore();

#endif