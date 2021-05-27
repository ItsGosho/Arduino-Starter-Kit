#include <Arduino.h>

const int controlPin1 = 12;
const int controlPin2 = 11;
const int enablePin = 10;
const int directionSwitchPin = 3;
const int onOffSwitchstateSwitchPin = 2;
const int potPin = A0;

int onOffSwitchState = 0;
int previousOnOffSwitchState = 0;
int directionSwitchState = 0;
int previousDirectionSwitchState = 0;

int motorEnabled = 0;
int motorSpeed = 0;
int motorDirection = 1;

void setup()
{
  pinMode(directionSwitchPin, INPUT);
  pinMode(onOffSwitchstateSwitchPin, INPUT);
  pinMode(controlPin1, OUTPUT);
  pinMode(controlPin2, OUTPUT);
  pinMode(enablePin, OUTPUT);

  digitalWrite(enablePin, LOW);
}

void loop()
{
  onOffSwitchState = digitalRead(onOffSwitchstateSwitchPin);
  delay(1);
  directionSwitchState = digitalRead(directionSwitchPin);
  motorSpeed = analogRead(potPin) / 4;

  if (onOffSwitchState != previousOnOffSwitchState)
  {
    if (onOffSwitchState == HIGH)
    {
      motorEnabled = !motorEnabled;
    }
  }

  if (directionSwitchState != previousDirectionSwitchState)
  {
    if (directionSwitchState == HIGH)
    {
      motorDirection = !motorDirection;
    }
  }

  if (motorDirection == 1)
  {
    digitalWrite(controlPin1, HIGH);
    digitalWrite(controlPin2, LOW);
  }
  else
  {
    digitalWrite(controlPin1, LOW);
    digitalWrite(controlPin2, HIGH);
  }

  if (motorEnabled == 1)
  {
    analogWrite(enablePin, motorSpeed);
  }
  else
  {
    analogWrite(enablePin, 0);
  }

  previousDirectionSwitchState = directionSwitchState;
  previousOnOffSwitchState = onOffSwitchState;
}