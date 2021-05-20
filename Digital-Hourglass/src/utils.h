#ifndef DIGITAL_HOURGLASS_UTILS
#define DIGITAL_HOURGLASS_UTILS

#include "timeunit.h"

namespace DigitalHourglass {

    void pinsMode(const unsigned char pinNumbers[], const unsigned char &pinNumbersSize,const char &mode);
    bool hasTimeElapsed(const unsigned long &value, const DigitalHourglass::TimeUnit &timeUnit);
}

#endif //DIGITAL_HOURGLASS_UTILS