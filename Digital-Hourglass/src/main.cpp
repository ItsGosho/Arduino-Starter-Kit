#include <Arduino.h>
#include "timeunit.h"

const unsigned char TILT_SENSOR_PIN_NUMBER = 8;
const unsigned char LED_PIN_COUNT = 6;
const unsigned char LED_PIN_NUMBERS[LED_PIN_COUNT] = {7, 6, 5, 4, 3, 2};

void setPinsToOutput(const unsigned char pinNumbers[]);
bool hasTimeElapsed(unsigned long value, TimeUnit timeUnit);
void reset();
void lightNext();

int pinIndex = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(TILT_SENSOR_PIN_NUMBER, INPUT);
  setPinsToOutput(LED_PIN_NUMBERS);
}

void loop()
{
  delay(1);

  if (hasTimeElapsed(1, SECOND))
  {
    if (pinIndex > LED_PIN_COUNT - 1)
    {
      reset();
    }
    else
    {
      lightNext();
    }
  }
  int tiltSensor = digitalRead(TILT_SENSOR_PIN_NUMBER);

  // if (tiltSensor == 0)
  // {
  //   reset();
  // }
}

void lightNext()
{
  digitalWrite(LED_PIN_NUMBERS[pinIndex], HIGH);
  pinIndex = pinIndex + 1;
}

void reset()
{
  for (size_t i = 0; i < LED_PIN_COUNT; i++)
  {
    digitalWrite(LED_PIN_NUMBERS[i], LOW);
  }

  pinIndex = 0;
}

bool hasTimeElapsed(unsigned long value, TimeUnit timeUnit)
{

  unsigned long equationValue;

  switch (timeUnit)
  {
  case SECOND:
    equationValue = value * 1000;
    break;

  case MINUTE:
    equationValue = value * 60 * 1000;
    break;

  case HOUR:
    equationValue = value * 60 * 60 * 1000;
    break;

  case DAY:
    equationValue = value * 24 * 60 * 60 * 1000;
    break;

  default:
    equationValue = value;
    break;
  }

  return (millis() % equationValue) == 0;
}

void setPinsToOutput(const unsigned char pinNumbers[])
{
  for (size_t i = 0; i < LED_PIN_COUNT; i++)
  {
    pinMode(pinNumbers[i], OUTPUT);
  }
}