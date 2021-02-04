#include <Arduino.h>
#include <Servo.h>
#include <SerialPrintF.h>

Servo servoMotor;

const short POTENTIOMETER_PIN_NUMBER = A0;
const short SERVO_MOTOR_PIN_NUMBER = 9;
const int SERIAL_BAUD = 9600;

int minPotValue = 1023;
int maxPotValue = 0;
int minServoAngle = 179;
int maxServoAngle = 0;

bool hasSecondsPassed(int seconds);

void setup()
{
  Serial.begin(SERIAL_BAUD);

  servoMotor.attach(SERVO_MOTOR_PIN_NUMBER);
}

void loop()
{
  int potentiometerValue = analogRead(POTENTIOMETER_PIN_NUMBER);
  int servoAngle = map(potentiometerValue, 0, 1023, 0, 179);

  if (potentiometerValue < minPotValue)
    minPotValue = potentiometerValue;

  if (potentiometerValue > maxPotValue)
    maxPotValue = potentiometerValue;

  if (servoAngle < minServoAngle)
    minServoAngle = servoAngle;

  if (servoAngle > maxServoAngle)
    maxServoAngle = servoAngle;

  if (hasSecondsPassed(10))
  {
    serial_printf(Serial, "\nPotentiometer min: %d max: %d dev: %d  |  Servo min: %d max: %d dev: %d expected: %d",
                  minPotValue,
                  maxPotValue,
                  maxPotValue - minPotValue,
                  minServoAngle,
                  maxServoAngle,
                  maxServoAngle - minServoAngle,
                  servoAngle);

    minPotValue = 1023;
    maxPotValue = 0;
    minServoAngle = 179;
    maxServoAngle = 0;
  }

  servoMotor.write(servoAngle);
  //delay(15);
}

int lastSecond = 0;

bool hasSecondsPassed(int seconds)
{
  long currentMillis = millis();
  int second = currentMillis / (seconds * 1000);

  if (second > lastSecond)
  {
    lastSecond = second;
    return true;
  }

  return false;
}