const int redPin = 9;
const int greenPin = 10;
const int bluePin = 11;

const int potRedPin = A0;
const int potGreenPin = A1;
const int potBluePin = A2;

int potRedValue;
int potGreenValue;
int potBlueValue;

const int maxAnalogValue = 255;
const int maxPotValue = 1023;

void setup()
{
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop()
{
  potRedValue = analogRead(potRedPin);
  potGreenValue = analogRead(potGreenPin);
  potBlueValue = analogRead(potBluePin);

  analogWrite(redPin, map(potRedValue, 0, maxPotValue, 0, maxAnalogValue));
  analogWrite(greenPin, map(potGreenValue, 0, maxPotValue, 0, maxAnalogValue));
  analogWrite(bluePin, map(potBlueValue, 0, maxPotValue, 0, maxAnalogValue));
}
