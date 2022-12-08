#ifndef JOYSTICK_MOVE_H
#define JOYSTICK_MOVE_H

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
        buttonPressed = true;
        Serial.println("acum");
      }
      else buttonPressed = false;
    } 
  }
  lastReading = reading;

  if( (minThreshold <= xValue && xValue <= maxThreshold) && (minThreshold <= yValue && yValue <= maxThreshold) ) {
    joyMoved = false;
    up = down = left = right = false;
  }

  if(yValue < minThreshold && joyMoved == false) { // up
    joyMoved = true;
    up = true;
  }

  if(yValue > maxThreshold && joyMoved == false) { // down
    joyMoved = true;
    down = true;
  }

  if(xValue < minThreshold && joyMoved == false) { // left
    joyMoved = true;
    left = true;
    Serial.println("left");
  }

  if(xValue > maxThreshold && joyMoved == false) { // right
    joyMoved = true;
    right = true;
    Serial.println("right");
  }
}

#endif