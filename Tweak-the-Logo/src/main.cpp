#include <Arduino.h>

#define BAUD_RATE 9600
#define POTENTIOMETER_PIN A0

void setup() {
    Serial.begin(BAUD_RATE);
}

void loop() {
    int potentiometerValue = analogRead(POTENTIOMETER_PIN);
    int serialWriteValue = potentiometerValue / 4;

    Serial.write(serialWriteValue);
    delay(1);
}