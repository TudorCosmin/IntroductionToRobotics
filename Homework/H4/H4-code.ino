const int buttonPin = 2;
const int pinX = A0;
const int pinY = A1;

const int latchPin = 11; // STCP to 12 on Shift Register
const int clockPin = 10; // SHCP to 11 on Shift Register
const int dataPin = 12; // DS to 14 on Shift Register

const int segD1 = 7;
const int segD2 = 6;
const int segD3 = 5;
const int segD4 = 4;

unsigned long elapsedTime = 0;
unsigned long lastBlinkTime = 0;
unsigned long intervalBlink = 300;

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
const unsigned long longDebounceDelay = 2000;
bool shortPress = false;
bool longPress = false;

const byte regSize = 8; // 1 byte aka 8 bits

int displayDigits[] = {
  segD1, segD2, segD3, segD4
};
const int displayCount = 4;

byte registers[regSize];
const int encodingsNumber = 16;

byte byteEncodings[encodingsNumber] = {
//A B C D E F G DP 
  B11111100, // 0 
  B01100000, // 1
  B11011010, // 2
  B11110010, // 3
  B01100110, // 4
  B10110110, // 5
  B10111110, // 6
  B11100000, // 7
  B11111110, // 8
  B11110110, // 9
  B11101110, // A
  B00111110, // b
  B10011100, // C
  B01111010, // d
  B10011110, // E
  B10001110  // F
};
byte dpEncoding = B00000001;
byte xorValue = B00000001;
bool displaySelector = true;
int selectedDisplay = 0;
int number[4] = {0, 0, 0, 0};

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);

  for (int i = 0; i < displayCount; i++) {
    pinMode(displayDigits[i], OUTPUT);
    digitalWrite(displayDigits[i], LOW);
  }
}

void loop() {
  inputData();

  if(displaySelector) {
    moveDisplaySelector();
    blinkDot();
  }
  else
    digitSelector();
  
  writeNumber();
}

void inputData() {
  xValue = analogRead(pinX);
  yValue = analogRead(pinY);
  reading = digitalRead(buttonPin);

  if(reading != lastReading)
    lastDebounceTime = millis();

  if(millis() - lastDebounceTime > shortDebounceDelay) {
    if(reading != buttonState) {
      buttonState = reading;

      if(buttonState == LOW) {
        displaySelector = !displaySelector;
        dpEncoding = xorValue;
      }
      else shortPress = !shortPress;
    } 
  }

  if(millis() - lastDebounceTime > longDebounceDelay) {
    if(shortPress == true) {
      if(buttonState == LOW)
        longPress = true;
      else
        longPress = false;
    }
  }

  if(shortPress && longPress)
    resetDisplay();
  
  lastReading = reading;
  if( (minThreshold <= xValue && xValue <= maxThreshold) && (minThreshold <= yValue && yValue <= maxThreshold) ) {
    joyMoved = false;
  }
}

void moveDisplaySelector() {
  if(xValue > maxThreshold && joyMoved == false) {
    selectedDisplay = max(selectedDisplay - 1, 0);
    joyMoved = true;
  }

  if(xValue < minThreshold && joyMoved == false) {
    selectedDisplay = min(selectedDisplay + 1, displayCount - 1);
    joyMoved = true;
  }
}

void digitSelector() {
  if(yValue > maxThreshold && joyMoved == false) {
    number[displayCount - 1 - selectedDisplay] = max(number[displayCount - 1 - selectedDisplay] - 1, 0);
    joyMoved = true;
  }

  if(yValue < minThreshold && joyMoved == false) {
    number[displayCount - 1 - selectedDisplay] = min(number[displayCount - 1 - selectedDisplay] + 1, encodingsNumber - 1);
    joyMoved = true;
  }
}

void writeNumber() {
  int index = displayCount - 1;
  int currentDigit = 0;
  int currentDisplay = 0;
  
  while(currentDisplay != displayCount) {
    currentDigit = number[index--];
    activateDisplay(currentDisplay, currentDigit);
    currentDisplay++;
    delay(2);
  }
}

void activateDisplay(int currentDisplay, int currentDigit) {
  for(auto display : displayDigits)
      digitalWrite(display, HIGH);

  if(currentDisplay == selectedDisplay)
    writeReg(byteEncodings[currentDigit] + dpEncoding);
  else
    writeReg(byteEncodings[currentDigit]);
    
  digitalWrite(displayDigits[currentDisplay], LOW);
}

void writeReg(byte encoding) {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, encoding);
  digitalWrite(latchPin, HIGH);
}

void blinkDot() {
  elapsedTime = millis();
  if(elapsedTime - lastBlinkTime > intervalBlink) {
    dpEncoding = dpEncoding ^ xorValue;
    lastBlinkTime = elapsedTime;
  }
}

void resetDisplay() {
  for(int i = 0; i < displayCount; i++)
    number[i] = 0;
  
  displaySelector = true;
  selectedDisplay = 0;
  shortPress = false;
  longPress = false;
}