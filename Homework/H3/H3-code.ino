int toCode(int pin) {
  return pin - 4;
}

int toPin(int code) {
  return code + 4;
}

const int buttonPin = 2;
const int pinX = A0;
const int pinY = A1;

const int pinA = 4;
const int pinB = 5;
const int pinC = 6;
const int pinD = 7;
const int pinE = 8;
const int pinF = 9;
const int pinG = 10;
const int pinDP = 11;

const int up = 0;
const int down = 1;
const int left = 2;
const int right = 3;

const int segSize = 9;
const int noOfNeighbours = 4;
bool stateSelector = false;

int selectedPinCode = toCode(pinDP);
byte selectedPinState = LOW;

int xValue = 0;
int yValue = 0;

bool joyMoved = false;
int digit = 0;
int minThreshold = 400;
int maxThreshold = 600;

unsigned long elapsedTime = 0;
unsigned long lastBlinkTime = 0;
unsigned long intervalBlink = 300;

byte buttonState = LOW;
byte lastReading = LOW;
byte reading = LOW;
unsigned long lastDebounceTime = 0;
const unsigned long shortDebounceDelay = 20;
const unsigned long longDebounceDelay = 1000;
bool shortPress = false;
bool longPress = false;

int segments[segSize] = { 
  pinA, pinB, pinC, pinD, pinE, pinF, pinG, pinDP
};

int state[segSize] = { 
  LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW
};

int neighMatrix[segSize][noOfNeighbours] = {
// 0 1 2 3 4 5 6  7 - codes
// A B C D E F G DP - pins

// up down left right -- neighbours
  {toCode(pinA), toCode(pinG), toCode(pinF), toCode(pinB)}, // A
  {toCode(pinA), toCode(pinG), toCode(pinF), toCode(pinB)}, // B
  {toCode(pinG), toCode(pinD), toCode(pinE), toCode(pinDP)}, // C
  {toCode(pinG), toCode(pinD), toCode(pinE), toCode(pinC)}, // D
  {toCode(pinG), toCode(pinD), toCode(pinE), toCode(pinC)}, // E
  {toCode(pinA), toCode(pinG), toCode(pinF), toCode(pinB)}, // F
  {toCode(pinA), toCode(pinD), toCode(pinG), toCode(pinG)}, // G
  { toCode(pinDP), toCode(pinDP), toCode(pinC), toCode(pinDP)}, // DP
};

void setup() {
  for (int i = 0; i < segSize; i++) {
    pinMode(segments[i], OUTPUT);
  }
  pinMode(buttonPin, INPUT_PULLUP);

  Serial.begin(9600);
}

void loop() {
  inputData();

  if(!stateSelector) {
    moveSelectedPin();
    blinkSelectedPin();
  }
  else {
    selector();
  }

  displayLeds();

  delay(100);
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
        stateSelector = !stateSelector;
        shortPress = !shortPress;
      }
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

void moveSelectedPin() {
  if(yValue > maxThreshold && joyMoved == false) {
    state[selectedPinCode] = selectedPinState;
    selectedPinCode = neighMatrix[selectedPinCode][down];
    selectedPinState = state[selectedPinCode];
    joyMoved = true;
  }
  
  if(yValue < minThreshold && joyMoved == false) {
    state[selectedPinCode] = selectedPinState;
    selectedPinCode = neighMatrix[selectedPinCode][up];
    selectedPinState = state[selectedPinCode];
    joyMoved = true;
  }

  if(xValue > maxThreshold && joyMoved == false) {
    state[selectedPinCode] = selectedPinState;
    selectedPinCode = neighMatrix[selectedPinCode][right];
    selectedPinState = state[selectedPinCode];
    joyMoved = true;
  }

  if(xValue < minThreshold && joyMoved == false) {
    state[selectedPinCode] = selectedPinState;
    selectedPinCode = neighMatrix[selectedPinCode][left];
    selectedPinState = state[selectedPinCode];
    joyMoved = true;
  }
}

void selector() {
  if( (xValue < minThreshold && joyMoved == false) || (xValue > maxThreshold && joyMoved == false) ) {
    state[selectedPinCode] = !state[selectedPinCode];
    joyMoved = true;
  }
  selectedPinState = state[selectedPinCode];
}

void blinkSelectedPin() {
  elapsedTime = millis();
  if(elapsedTime - lastBlinkTime > intervalBlink) {
    state[selectedPinCode] = !state[selectedPinCode];
    lastBlinkTime = elapsedTime;
  }
}

void displayLeds() {
  for(int i = 0; i < segSize; i++) {
    digitalWrite(segments[i], state[i]);
  }
}

void resetDisplay() {
  for(int i = 0; i < segSize; i++) {
    state[i] = LOW;
  }
  selectedPinCode = toCode(pinDP);
  selectedPinState = LOW;
  stateSelector = false;
}
