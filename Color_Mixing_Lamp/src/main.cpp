#include <Arduino.h>
#include <SerialPrintF.h>

//For pin numbers we don't need anything more than 256 :D
const short redLEDPin = 10;
const short greenLEDPin = 9;
const short blueLEDPin = 11;

const short redSensorPin = A0;
const short greenSensorPin = A1;
const short blueSensorPin = A2;

int redValue = 0;
int greenValue = 0;
int blueValue = 0;

int redSensorValue = 0;
int greenSensorValue = 0;
int blueSensorValue = 0;

void setup()
{
  Serial.begin(9600);

  pinMode(greenLEDPin, OUTPUT);
  pinMode(redLEDPin, OUTPUT);
  pinMode(blueLEDPin, OUTPUT);
}

void loop()
{
  redSensorValue = analogRead(redSensorPin);
  delay(5);
  greenSensorValue = analogRead(greenSensorPin);
  delay(5);
  blueSensorValue = analogRead(blueSensorPin);

  serial_printf(Serial, "Raw Sensor Values  Red: %d Green: %d Blue: %d", redSensorValue, greenSensorValue, blueSensorValue);

  redValue = redSensorValue / 4;
  greenValue = greenSensorValue / 4;
  blueValue = blueSensorValue / 4;

  serial_printf(Serial, "Mapped Sensor Values  Red: %d Green: %d Blue: %d", redValue, greenValue, blueValue);

  analogWrite(redLEDPin, redValue);
  analogWrite(greenLEDPin, greenValue);
  analogWrite(blueLEDPin, blueValue);
}