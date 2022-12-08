#ifndef VAEIABLES_H
#define VARIABLES_H

#include <LiquidCrystal.h>
#include <LedControl.h>
#include <EEPROM.h>
#include <ezBuzzer.h>

// ------------------------------------------------ joystick variables
const byte buttonPin = 2;
const byte pinX = A0;
const byte pinY = A1;

bool changedMenuItem = false;
bool up = false;
bool down = false;
bool left = false;
bool right = false;
bool buttonPressed = false;

int xValue = 0;
int yValue = 0;
bool joyMoved = false;
int minThreshold = 400;
int maxThreshold = 600;

byte buttonState = LOW;
byte lastReading = LOW;
byte reading = LOW;
unsigned long lastDebounceTime = 0;
const unsigned long shortDebounceDelay = 20;
bool shortPress = false;

// ------------------------------------------------ buzzer variables
const int buzzerPin = A2;
ezBuzzer buzzer(buzzerPin);

int yepBeep[] = { NOTE_B5 };
int nopeBeep[] = { NOTE_E5 };
int beepDuration[] = { 8 };

// const unsigned long intervalBuzzTime = 100;
// unsigned long lastBuzzTime = 0;
// unsigned int buzzTone = 600;
// const unsigned int yepBuzzTone = 1000;
// const unsigned int nopeBuzzTone = 600;



// ------------------------------------------------ menu variables
const byte rs = 9;
const byte en = 8;
const byte d4 = 7;
const byte d5 = 6;
const byte d6 = 3; // era 5
const byte d7 = 4;
const byte lcdBrightnessPin = 5; // era 3
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

byte currentItem = 0;
byte minCurrentItem = 0;
byte maxCurrentItem = 4;

String currentName = "OMAR";
byte selectNamePos = 0;

byte highscoreLevel = 0;
byte highscorePosition = 1;

byte currentLevel = 0;
bool selectLevel = false;

byte lcdBrightness = 128;
byte lcdBrightnessAddress = 0;
bool soundOn = false;
byte soundAddress = 2;

bool resetInfoStartTime = true;
unsigned long infoStartTime = 0;
int startLetter = 0;

// game states:
byte gameState = 0;
const byte initialGS = 0;
const byte runGS = 1;
const byte highscoreGS = 2;
const byte settingsGS = 3;
const byte creditsGS = 4;
const byte howToPlayGS = 5;
const byte enterNameGS = 6;
const byte selectLevelGS = 7;
const byte lcdBrightnessGS = 9;
const byte matrixBrightnessGS = 10;
const byte selectSoundGS = 11;
const byte endGameGS = 12;

String mainMenuItems[5] = {
  "Start game",
  "Highscore",
  "Settings",
  "Credits",
  "How to play"
};

String settingsMenuItems[6] = {
  "Enter name",
  "Level    0",
  "LCD bright",
  "Matrix bright",
  "Sound     ",
  "Back"
};

// ------------------------------------------------ messages
char *creditsMessage = "                Incredible Maze was made by: Tudor Cosmin Oanea, github.com/TudorCosmin                ";
char *howToPlayMessage = "                from top-left to bottom-right it's not that hard                ";


// ------------------------------------------------ custom characters
byte arrowUpChar[8] = {
	0b00000,
	0b00000,
	0b00100,
	0b01110,
	0b11111,
	0b00000,
	0b00000,
	0b00000
};
byte arrowUpCode = 0;

byte arrowDownChar[8] = {
	0b00000,
	0b00000,
	0b00000,
	0b11111,
	0b01110,
	0b00100,
	0b00000,
	0b00000
};
byte arrowDownCode = 1;

byte arrowLeftChar[8] = {
	0b00000,
	0b00000,
	0b00011,
	0b01111,
	0b01111,
	0b00011,
	0b00000,
	0b00000
};
byte arrowLeftCode = 2;

byte arrowRightChar[8] = {
	0b00000,
	0b00000,
	0b11000,
	0b11110,
	0b11110,
	0b11000,
	0b00000,
	0b00000
};
byte arrowRightCode = 3;

byte slidingBarChar[8] = {
	0b00000,
	0b11111,
	0b00000,
	0b11111,
	0b00000,
	0b11111,
	0b00000,
	0b00000
};
byte slidingBarCode = 4;

// ------------------------------------------------ matrix variables
const byte dinPin = 12;
const byte clockPin = 11;
const byte loadPin = 10;

LedControl matrix = LedControl(dinPin, clockPin, loadPin, 1); // DIN, CLK, LOAD, No. DRIVER
byte matrixBrightness = 10;
byte matrixBrightnessAddress = 1;

const uint64_t images[] = {
  0x004242425a664200,
  0xdbdbdb1b18180000,
  0x03070e7c88880830,
  0x3c4299858599423c,
  0x0800080810202418,
  0xffffffffffffffff
};

// ------------------------------------------------ levels and gameplay:

unsigned long startGameTime = 0;
unsigned long elapsedTime = 0;
bool win = false;

// position of top-left corner of shown map
byte mapX = 0;
byte mapY = 0;
byte border = 2;

int playerX = 1;
int playerY = 1;

byte mapSize = 15; // I may increase this in the future
int levels[][16][16] = {
{
  // level 1
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1},
  {1, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
}};
const byte maxLevel = 0;





// https://github.com/robsoncouto/arduino-songs
// int melody[] = {
//   NOTE_AS4, NOTE_AS4, NOTE_AS4,
//   NOTE_F5, NOTE_C6,
//   NOTE_AS5, NOTE_A5, NOTE_G5, NOTE_F6, NOTE_C6,  
//   NOTE_AS5, NOTE_A5, NOTE_G5, NOTE_F6, NOTE_C6,  
//   NOTE_AS5, NOTE_A5, NOTE_AS5, NOTE_G5, NOTE_C5, NOTE_C5, NOTE_C5,
//   NOTE_F5, NOTE_C6,
//   NOTE_AS5, NOTE_A5, NOTE_G5, NOTE_F6, NOTE_C6,  
  
//   NOTE_AS5, NOTE_A5, NOTE_G5, NOTE_F6, NOTE_C6, 
//   NOTE_AS5, NOTE_A5, NOTE_AS5, NOTE_G5, NOTE_C5, NOTE_C5, 
//   NOTE_D5, NOTE_D5, NOTE_AS5, NOTE_A5, NOTE_G5, NOTE_F5,8,
//   NOTE_F5, NOTE_G5, NOTE_A5, NOTE_G5, NOTE_D5, NOTE_E5, NOTE_C5, NOTE_C5,
//   NOTE_D5, NOTE_D5, NOTE_AS5, NOTE_A5, NOTE_G5, NOTE_F5,
  
//   NOTE_C6, NOTE_G5, NOTE_G5, 0, NOTE_C5,
//   NOTE_D5, NOTE_D5, NOTE_AS5, NOTE_A5, NOTE_G5, NOTE_F5,
//   NOTE_F5, NOTE_G5, NOTE_A5, NOTE_G5, NOTE_D5, NOTE_E5,NOTE_C6, NOTE_C6,
//   NOTE_F6, NOTE_DS6, NOTE_CS6, NOTE_C6, NOTE_AS5, NOTE_GS5, NOTE_G5, NOTE_F5,
//   NOTE_C6
// };

// int noteDurations[] = {
//   8, 8, 8,
//   2, 2,
//   8, 8, 8, 2, 4,  
//   8, 8, 8, 2, 4,  
//   8, 8, 8, 2, 8, 8, 8,
//   2, 2,
//   8, 8, 8, 2, 4,  
  
//   8, 8, 8, 2, 4,  
//   8, 8, 8, 2, -8, 16, 
//   -4, 8, 8, 8, 8, 8,
//   8, 8, 8, 4, 8, 4, -8, 16,
//   -4, 8, 8, 8, 8, 8,
  
//   -8, 16, 2, 8, 8,
//   -4, 8, 8, 8, 8, 8,
//   8, 8, 8, 4, 8, 4, -8, 16,
//   4, 8, 4, 8, 4, 8, 4, 8,
//   1
// };


#endif