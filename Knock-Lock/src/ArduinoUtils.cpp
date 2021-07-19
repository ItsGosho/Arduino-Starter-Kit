#include "ArduinoUtils.h"
#include <Arduino.h>

const short BLINK_LED_DEFAULT_INTERVAL_MS = 100;

void ArduinoUtils::blinkLed(short ledPin) {
    blinkLed(ledPin, BLINK_LED_DEFAULT_INTERVAL_MS);
}

void ArduinoUtils::blinkLed(short ledPin, int interval) {
    digitalWrite(ledPin, HIGH);
    delay(interval);
    digitalWrite(ledPin, LOW);
}
