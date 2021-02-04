#include <Arduino.h>
#include <Servo.h>
#include <SerialPrintF.h>

Servo servoMotor;

const short POTENTIOMETER_PIN_NUMBER = A0;
const short SERVO_MOTOR_PIN_NUMBER = 9;
const int SERIAL_BAUD = 9600;

int minPotValueLastSec = 1023;
int maxPotValueLastSec = 0;
int minServoAngleLastSec = 179;
int maxServoAngleLastSec = 0;

bool hasSecondPassed();

void setup()
{
  Serial.begin(SERIAL_BAUD);

  servoMotor.attach(SERVO_MOTOR_PIN_NUMBER);
}

void loop()
{
  int potentiometerValue = analogRead(POTENTIOMETER_PIN_NUMBER);
  int servoAngle = map(potentiometerValue, 0, 1023, 0, 179);

  if (potentiometerValue < minPotValueLastSec)
    minPotValueLastSec = potentiometerValue;

  if (potentiometerValue > maxPotValueLastSec)
    maxPotValueLastSec = potentiometerValue;

  if (servoAngle < minServoAngleLastSec)
    minServoAngleLastSec = servoAngle;

  if (servoAngle > maxServoAngleLastSec)
    maxServoAngleLastSec = servoAngle;

  if (hasSecondPassed())
  {
    serial_printf(Serial, "\nPotentiometer MIN: %d MAX: %d, Servo MIN: %d MAX: %d DESIRED: %d",
                  minPotValueLastSec,
                  maxPotValueLastSec,
                  minServoAngleLastSec,
                  maxServoAngleLastSec,
                  servoAngle);

    minPotValueLastSec = 1023;
    maxPotValueLastSec = 0;
    minServoAngleLastSec = 179;
    maxServoAngleLastSec = 0;
  }

  //serial_printf(Serial, "\nPotentiometer Value: %d, Servo Angle: %d", potentiometerValue, servoAngle);

  servoMotor.write(servoAngle);
  //delay(15);
}

int lastSecond = 0;

bool hasSecondPassed()
{
  long currentMillis = millis();
  int second = currentMillis / 1000;

  if (second > lastSecond)
  {
    lastSecond = second;
    return true;
  }

  return false;
}