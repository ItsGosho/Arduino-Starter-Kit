#ifndef DIGITAL_HOURGLASS_SENSITIVE_TILT_SENSOR
#define DIGITAL_HOURGLASS_SENSITIVE_TILT_SENSOR

namespace DigitalHourglass
{
    class TiltSensor
    {

    private:
        short pinNumber;
        short startPosition;
        unsigned long startMs = 0;
        unsigned long endMs = 0;
        unsigned long sensitivityMs;

    public:
        TiltSensor(short pinNumber, unsigned long sensitivityMs);
        void checkFlip(void (*callback)(void));
    };
}

#endif //DIGITAL_HOURGLASS_SENSITIVE_TILT_SENSOR