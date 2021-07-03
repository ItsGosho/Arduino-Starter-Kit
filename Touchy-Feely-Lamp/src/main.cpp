#include <Arduino.h>
#include <CapacitiveSensor.h>

#define BAUD_RATE 9600
#define LED_PIN 9
#define RECEIVE_PIN 10
#define SENDER_PIN 11
#define THRESHOLD 1000
#define SENSOR_SAMPLES 30

CapacitiveSensor capacitiveSensor(SENDER_PIN, RECEIVE_PIN);

void setup() {
    Serial.begin(BAUD_RATE);
    pinMode(LED_PIN, OUTPUT);
}

void loop() {
    long sensorValue = capacitiveSensor.capacitiveSensor(SENSOR_SAMPLES);
    Serial.println(sensorValue);

    if (sensorValue > THRESHOLD) {
        digitalWrite(LED_PIN, HIGH);
    } else {
        digitalWrite(LED_PIN, LOW);
    }

    delay(10);
}