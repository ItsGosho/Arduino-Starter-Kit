#include <Arduino.h>
#include <MemoryFree.h>
#include <pgmStrToRAM.h>

int switchState = 0;

const int SERIAL_BAUD = 9600;
const int DELAY_INTERVALS_MS = 250;

const int LED_1_PIN_NUMBER = 3;
const int LED_2_PIN_NUMBER = 4;
const int LED_3_PIN_NUMBER = 5;
const int SWITCH_STATE_PIN_NUMBER = 2;

const int BLINK_TIMES = 10;
const int BLINK_INTERVAL_MS = 300;

void blinkLEDPort(int);

void setup()
{
  Serial.begin(SERIAL_BAUD);

  pinMode(LED_1_PIN_NUMBER, OUTPUT);
  pinMode(LED_2_PIN_NUMBER, OUTPUT);
  pinMode(LED_3_PIN_NUMBER, OUTPUT);
  pinMode(SWITCH_STATE_PIN_NUMBER, INPUT);

  blinkLEDPort(LED_1_PIN_NUMBER);
}

void loop()
{
  switchState = digitalRead(SWITCH_STATE_PIN_NUMBER);

  switch (switchState)
  {

  case LOW:

    digitalWrite(LED_1_PIN_NUMBER, HIGH);
    digitalWrite(LED_2_PIN_NUMBER, LOW);
    digitalWrite(LED_3_PIN_NUMBER, LOW);

    break;

  case HIGH:

    digitalWrite(LED_1_PIN_NUMBER, LOW);
    digitalWrite(LED_2_PIN_NUMBER, LOW);
    digitalWrite(LED_3_PIN_NUMBER, HIGH);

    delay(DELAY_INTERVALS_MS);

    digitalWrite(LED_2_PIN_NUMBER, HIGH);
    digitalWrite(LED_3_PIN_NUMBER, LOW);

    delay(DELAY_INTERVALS_MS);

    break;

  default:
    Serial.println((String) "Switch state: " + switchState + " is not yet handled!");
    break;
  }

  delay(DELAY_INTERVALS_MS);
}

void blinkLEDPort(int portNumber)
{
  for (int i = 0; i < BLINK_TIMES; i++)
  {
    digitalWrite(LED_1_PIN_NUMBER, HIGH);
    delay(BLINK_INTERVAL_MS);
    digitalWrite(LED_1_PIN_NUMBER, LOW);
    delay(BLINK_INTERVAL_MS);
  }
}