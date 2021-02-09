#include <Arduino.h>


int notes[] = {262, 294, 330, 349};

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  int keyVal = analogRead(A0);

  if (keyVal == 1024)
  {
    Serial.println(notes[0]);
    tone(8, notes[0]);
  }
  else if (keyVal >= 990 && keyVal <= 1010)
  {
    Serial.println(notes[1]);
    tone(8, notes[1]);
  }
  else if (keyVal >= 505 && keyVal <= 515)
  {
    Serial.println(notes[2]);
    tone(8, notes[2]);
  }
  else if (keyVal >= 5 && keyVal <= 10)
  {
    Serial.println(notes[3]);
    tone(8, notes[3]);
  }
  else
  {
    noTone(8);
  }
}