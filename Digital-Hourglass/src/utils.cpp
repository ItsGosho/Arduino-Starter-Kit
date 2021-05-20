#include <Arduino.h>
#include "utils.h"
#include "timeunit.h"
#include "msconverter.h"

void DigitalHourglass::pinsMode(const unsigned char pinNumbers[], const unsigned char &pinNumbersSize, const char &mode)
{
    for (size_t i = 0; i < pinNumbersSize; i++)
    {
        pinMode(pinNumbers[i], mode);
    }
}

bool DigitalHourglass::hasTimeElapsed(const unsigned long &value, const DigitalHourglass::TimeUnit &timeUnit)
{
  unsigned long ms = DigitalHourglass::convertToMS(value, timeUnit);

  return (millis() % ms) == 0;
}
