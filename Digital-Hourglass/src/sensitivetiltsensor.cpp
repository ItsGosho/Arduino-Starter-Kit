#include <Arduino.h>
#include "sensitivetiltsensor.h"

DigitalHourglass::TiltSensor::TiltSensor(short pinNumber, unsigned long sensitivityMs)
{
    this->pinNumber = pinNumber;
    this->sensitivityMs = sensitivityMs;
    pinMode(this->pinNumber, INPUT);
    this->startPosition = digitalRead(this->pinNumber);
}

void DigitalHourglass::TiltSensor::checkFlip(void (*callback)(void))
{
    char tiltSensorValue = digitalRead(this->pinNumber);

    if (tiltSensorValue == this->startPosition)
    {
        if (this->startMs != 0)
            this->endMs = millis();

        unsigned long tiltSensorMsStreak = this->endMs - this->startMs;

        if (tiltSensorMsStreak >= this->sensitivityMs)
            callback();

        this->startMs = 0;
        this->endMs = 0;
    }
    else
    {
        if (this->startMs == 0)
            this->startMs = millis();
    }
}