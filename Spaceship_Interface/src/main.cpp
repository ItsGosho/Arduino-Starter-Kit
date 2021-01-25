#include <Arduino.h>
#include <MemoryFree.h>
#include <pgmStrToRAM.h>

int switchState = 0;

const int SERIAL_BAUD = 9600;
const int DELAY_INTERVALS_MS = 250;

void setup() {
  Serial.begin(SERIAL_BAUD);
  
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(2, INPUT);
}

void loop() {
  switchState = digitalRead(2);

  if(switchState == LOW) {
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
  }else {
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);

    delay(DELAY_INTERVALS_MS);

    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);

    delay(DELAY_INTERVALS_MS);
  }

  delay(DELAY_INTERVALS_MS);
}