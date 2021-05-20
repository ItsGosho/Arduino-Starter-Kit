#include <Arduino.h>
#include "timeunit.h"
#include "msconverter.h"
#include "SerialPrintF.h"
#include "sensitivetiltsensor.h"

const unsigned char TILT_SENSOR_PIN_NUMBER = 8;
const unsigned char TILT_SENSOR_SENSITIVITY_MS = 135;
const unsigned char LED_PIN_COUNT = 6;
const unsigned char LED_PIN_NUMBERS[LED_PIN_COUNT] = {7, 6, 5, 4, 3, 2};

void setPinsToOutput(const unsigned char pinNumbers[]);
bool hasTimeElapsed(const unsigned long &value, const DigitalHourglass::TimeUnit &timeUnit);
void reset();
void lightNext();

int pinIndex = 0;
unsigned long start = 0;
unsigned long end = 0;
short tiltStartPosition;
DigitalHourglass::TiltSensor tiltSensor = DigitalHourglass::TiltSensor(TILT_SENSOR_PIN_NUMBER, TILT_SENSOR_SENSITIVITY_MS);

void onTiltSensorFlip()
{
  //  Serial.println("FLIP!");
  reset();
}

void setup()
{
  Serial.begin(9600);
  setPinsToOutput(LED_PIN_NUMBERS);
}

/**
 * 
 * 1. Use the library for logging, which was used in the older task solutions.
 * 2. Move somehow the logic of the titlt sensor, which will be under the SensitiveTiltSensor, which will accept sensitivity ()
 * 3. Look again the whole code, methods, variables and so on.
**/
void loop()
{
  delay(1);

  if (hasTimeElapsed(1, DigitalHourglass::TimeUnit::SECOND))
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

  tiltSensor.checkFlip(onTiltSensorFlip);
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

bool hasTimeElapsed(const unsigned long &value, const DigitalHourglass::TimeUnit &timeUnit)
{
  unsigned long ms = DigitalHourglass::convertToMS(value, timeUnit);

  return (millis() % ms) == 0;
}

void setPinsToOutput(const unsigned char pinNumbers[])
{
  for (size_t i = 0; i < LED_PIN_COUNT; i++)
  {
    pinMode(pinNumbers[i], OUTPUT);
  }
}