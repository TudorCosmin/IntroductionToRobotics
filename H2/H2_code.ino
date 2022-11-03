const int buttonPin = 2;
const int greenCarPin = 13;
const int yellowCarPin = 12;
const int redCarPin = 11;
const int greenManPin = 10;
const int redManPin = 9;
const int buzzerPin = 8;

byte buttonState = LOW;
byte lastReading = LOW;
byte reading = LOW;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 20;

bool running = false;
unsigned long runningStartTime = 0;
unsigned long elapsedTime = 0;
const unsigned long stateChangeDelay = 10;
unsigned long lastBuzzChangeTime = 0;

const unsigned long greenToYellowTime = 8000; // state 1
const unsigned long yellowTime = 3000;        // state 2
const unsigned long redTime = 8000;           // state 3
const unsigned long redToGreenTime = 4000;    // state 4

bool buzz = false;
const unsigned int buzzDelay = 10;
bool resetNeeded = true;

const unsigned long lowBuzzTime = 700;
const unsigned long intervalLowBuzzTime = 500;
const int buzzerLowTone = 600;
const unsigned long highBuzzTime = 400;
const unsigned long intervalHighBuzzTime = 250;
const int buzzerHighTone = 1000;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(greenCarPin, OUTPUT);
  pinMode(yellowCarPin, OUTPUT);
  pinMode(redCarPin, OUTPUT);
  pinMode(greenManPin, OUTPUT);
  pinMode(redManPin, OUTPUT);
  greenForCars();
  Serial.begin(9600);
}

void loop() {
  if(!running) {
    reading = digitalRead(buttonPin);

    if(reading != lastReading)
      lastDebounceTime = millis();

    if(millis() - lastDebounceTime > debounceDelay) {
      if(reading != buttonState) {
        buttonState = reading;

        if(buttonState == LOW) {
          running = true;
          runningStartTime = millis();
        }
      }
    }
    lastReading = reading;
    resetNeeded = true;
  }
  else { // if(running)
    elapsedTime = millis() - runningStartTime;
    
    if(elapsedTime + stateChangeDelay < greenToYellowTime) { // state 1
      greenForCars();
    }
    else if( (elapsedTime > greenToYellowTime) && (elapsedTime + stateChangeDelay < greenToYellowTime + yellowTime) ) { // state 2
      yellowForCars();
    }
    else if( (elapsedTime > greenToYellowTime + yellowTime) && (elapsedTime + stateChangeDelay < greenToYellowTime + yellowTime + redTime) ) { // state 3
      redForCars();
      buzzStart(intervalLowBuzzTime, lowBuzzTime, buzzerLowTone, false);
    }
    else if((elapsedTime > greenToYellowTime + yellowTime + redTime) && (elapsedTime + stateChangeDelay < greenToYellowTime + yellowTime + redTime + redToGreenTime) ) { // state 4
      if(resetNeeded) {
        lastBuzzChangeTime = 0;
        resetNeeded = false;
      }
      buzzStart(intervalHighBuzzTime, highBuzzTime, buzzerHighTone, true);
    }
    else if(elapsedTime > greenToYellowTime + yellowTime + redTime + redToGreenTime) { // stop running
      deactivateBuzzer(true);
      lastBuzzChangeTime = 0;

      greenForCars();
      running = false;
    }
  }
}

void buzzStart(unsigned long intervalBuzzTime, int buzzTime, int buzzTone,  bool withLed) {
  // elapsed time since last change
  unsigned int elapsedBuzzTime = elapsedTime - lastBuzzChangeTime;

  if(lastBuzzChangeTime == 0) {
    activateBuzzer(buzzTone, withLed);
  }
  if(!buzz) {
    if( (intervalBuzzTime - buzzDelay < elapsedBuzzTime) && (elapsedBuzzTime < intervalBuzzTime) ) {
      activateBuzzer(buzzTone, withLed);
    }
  }
  else {
    if( (buzzTime - buzzDelay < elapsedBuzzTime) && (elapsedBuzzTime < buzzTime) ) {
      deactivateBuzzer(withLed);
    }
  }
}

void activateBuzzer(int buzzTone, bool withLed) {
  buzz = true;
  tone(buzzerPin, buzzTone);
  if(withLed) { // state 4
    redForCars();
  }
  lastBuzzChangeTime = millis() - runningStartTime;
}

void deactivateBuzzer(bool withLed) {
  buzz = false;
  noTone(buzzerPin);
  if(withLed) { // state 4
    redToGreenForCars();
  }
  lastBuzzChangeTime = millis() - runningStartTime;
}

void greenForCars() {
  digitalWrite(greenCarPin, HIGH);
  digitalWrite(yellowCarPin, LOW);
  digitalWrite(redCarPin, LOW);
  digitalWrite(greenManPin, LOW);
  digitalWrite(redManPin, HIGH);
}

void yellowForCars() {
  digitalWrite(greenCarPin, LOW);
  digitalWrite(yellowCarPin, HIGH);
  digitalWrite(redCarPin, LOW);
  digitalWrite(greenManPin, LOW);
  digitalWrite(redManPin, HIGH);
}

void redForCars() {
  digitalWrite(greenCarPin, LOW);
  digitalWrite(yellowCarPin, LOW);
  digitalWrite(redCarPin, HIGH);
  digitalWrite(greenManPin, HIGH);
  digitalWrite(redManPin, LOW);
}

void redToGreenForCars() {
  digitalWrite(greenCarPin, LOW);
  digitalWrite(yellowCarPin, LOW);
  digitalWrite(redCarPin, HIGH);
  digitalWrite(greenManPin, LOW);
  digitalWrite(redManPin, LOW);
}
