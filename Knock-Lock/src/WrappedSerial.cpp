#include <WrappedSerial.h>
#include <Arduino.h>

void WrappedSerial::begin(int baudRate) {
#ifndef DISABLE_SERIAL
    Serial.begin(baudRate);
#endif
}

void WrappedSerial::println(const char* text) {
#ifndef DISABLE_SERIAL
    Serial.println(text);
#endif
}
