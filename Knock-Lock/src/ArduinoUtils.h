#ifndef KNOCK_LOCK_ARDUINOUTILS_H
#define KNOCK_LOCK_ARDUINOUTILS_H

#include "Arduino.h"

namespace ArduinoUtils {

    template<typename T, size_t N>
    void setPinsMode(T (& pinNumbers)[N], const byte& mode) {
        for (size_t i = 0; i < N; i++) {
            pinMode(pinNumbers[i], mode);
        }
    }

    void blinkLed(short ledPin);
    void blinkLed(short ledPin, int interval);
};


#endif //KNOCK_LOCK_ARDUINOUTILS_H
