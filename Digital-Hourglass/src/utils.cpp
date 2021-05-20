#include <Arduino.h>
#include "utils.h"

void DigitalHourglass::pinsMode(const unsigned char pinNumbers[], const unsigned char &pinNumbersSize, const char &mode)
{
    for (size_t i = 0; i < pinNumbersSize; i++)
    {
        pinMode(pinNumbers[i], mode);
    }
}
