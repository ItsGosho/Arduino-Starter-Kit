#include <Arduino.h>
#include "timeunit.h"
#include "SerialPrintF.h"
#include "sensitivetiltsensor.h"
#include "utils.h"

const unsigned char TILT_SENSOR_PIN_NUMBER = 8;
const unsigned char TILT_SENSOR_SENSITIVITY_MS = 135;
const unsigned char LED_PIN_COUNT = 6;
const unsigned char LED_PIN_NUMBERS[LED_PIN_COUNT] = {7, 6, 5, 4, 3, 2};

void resetLeds();
void lightNextLed();
bool hasNoMoreLeds();

int reachedLedIndex = 0;
DigitalHourglass::TiltSensor tiltSensor = DigitalHourglass::TiltSensor(TILT_SENSOR_PIN_NUMBER, TILT_SENSOR_SENSITIVITY_MS);

void setup()
{
  Serial.begin(9600);
  DigitalHourglass::pinsMode(LED_PIN_NUMBERS, LED_PIN_COUNT, OUTPUT);
}

void loop()
{
  delay(1);

  if (DigitalHourglass::hasTimeElapsed(1, DigitalHourglass::TimeUnit::SECOND))
  {

    if (hasNoMoreLeds())
      resetLeds();
    else
      lightNextLed();
  }

  tiltSensor.checkFlip(resetLeds);
}

bool hasNoMoreLeds()
{
  return reachedLedIndex > LED_PIN_COUNT - 1;
}

void lightNextLed()
{
  digitalWrite(LED_PIN_NUMBERS[reachedLedIndex], HIGH);
  reachedLedIndex++;
}

void resetLeds()
{
  DigitalHourglass::digitalWrites(LED_PIN_NUMBERS, LED_PIN_COUNT, LOW);

  reachedLedIndex = 0;
}