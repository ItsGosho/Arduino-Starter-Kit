#include <Arduino.h>
#include <CapacitiveSensor.h>

CapacitiveSensor capacitiveSensor(11, 10);

int threshold = 1000;
const int ledPin = 9;

void setup() {
    Serial.begin(9600);
    pinMode(ledPin, OUTPUT);
}

void loop() {
    long sensorValue = capacitiveSensor.capacitiveSensor(30);
    Serial.println(sensorValue);

    if (sensorValue > threshold) {
        digitalWrite(ledPin, HIGH);
    } else {
        digitalWrite(ledPin, LOW);
    }

    delay(10);
}