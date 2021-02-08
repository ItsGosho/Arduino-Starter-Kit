#include <Arduino.h>

const short LED_SYNC_FINISHED_PIN_NUMBER = 13;
const short PIEZO_PIN_NUMBER = 8;
const short PHOTOTRANSISTOR_PIN_NUMBER = A0;
const int SYNC_TIME_MS = 5000;

int phototransistorLow = 1023;
int phototransistorHigh = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(LED_SYNC_FINISHED_PIN_NUMBER, OUTPUT);
  digitalWrite(LED_SYNC_FINISHED_PIN_NUMBER, HIGH);

  while (millis() < SYNC_TIME_MS)
  {
    int phototransistorValue = analogRead(PHOTOTRANSISTOR_PIN_NUMBER);

    if (phototransistorValue > phototransistorHigh)
      phototransistorHigh = phototransistorValue;

    if (phototransistorValue < phototransistorLow)
      phototransistorLow = phototransistorValue;
  }

  digitalWrite(LED_SYNC_FINISHED_PIN_NUMBER, LOW);
  Serial.println(phototransistorLow);
  Serial.println(phototransistorHigh);
}

void loop()
{
  int phototransistorValue = analogRead(PHOTOTRANSISTOR_PIN_NUMBER);

  int pitch = map(phototransistorValue, phototransistorLow, phototransistorHigh, 50, 4000);

  tone(PIEZO_PIN_NUMBER, pitch, 20);

  delay(10);
}