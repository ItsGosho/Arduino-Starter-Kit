#ifndef DIGITAL_HOURGLASS_MS_CONVERTER
#define DIGITAL_HOURGLASS_MS_CONVERTER

#include "timeunit.h"

namespace DigitalHourglass
{
    unsigned long convertToMS(unsigned long ms, TimeUnit timeUnit)
    {
        switch (timeUnit)
        {
        case SECOND:
            return ms * 1000;

        case MINUTE:
            return ms * 60 * 1000;

        case HOUR:
            return ms * 60 * 60 * 1000;

        case DAY:
            return ms * 24 * 60 * 60 * 1000;

        default:
            return ms;
        }
    }
}

#endif //DIGITAL_HOURGLASS_MS_CONVERTER