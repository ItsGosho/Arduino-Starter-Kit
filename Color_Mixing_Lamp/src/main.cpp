#include <Arduino.h>
#include <SerialPrintF.h>

//For pin numbers we don't need anything more than 256 :D
const short RGB_LED_RED_PIN_NUMBER = 9;
const short RGB_LED_GREEN_PIN_NUMBER = 10;
const short RGB_LED_BLUE_PIN_NUMBER = 11;

const short PHOTORESISTOR_RED_PIN_NUMBER = A0;
const short PHOTORESISTOR_GREEN_PIN_NUMBER = A1;
const short PHOTORESISTOR_BLUE_PIN_NUMBER = A2;

int redValue = 0;
int greenValue = 0;
int blueValue = 0;

int redSensorValue = 0;
int greenSensorValue = 0;
int blueSensorValue = 0;

void setup()
{
  Serial.begin(9600);

  pinMode(RGB_LED_RED_PIN_NUMBER, OUTPUT);
  pinMode(RGB_LED_GREEN_PIN_NUMBER, OUTPUT);
  pinMode(RGB_LED_BLUE_PIN_NUMBER, OUTPUT);
}

void loop()
{
  redSensorValue = analogRead(PHOTORESISTOR_RED_PIN_NUMBER);
  delay(5);
  greenSensorValue = analogRead(PHOTORESISTOR_GREEN_PIN_NUMBER);
  delay(5);
  blueSensorValue = analogRead(PHOTORESISTOR_BLUE_PIN_NUMBER);

  serial_printf(Serial, "Raw Sensor Values  Red: %d Green: %d Blue: %d\n", redSensorValue, greenSensorValue, blueSensorValue);

  redValue = redSensorValue / 4;
  greenValue = greenSensorValue / 4;
  blueValue = blueSensorValue / 4;

  serial_printf(Serial, "Mapped Sensor Values  Red: %d Green: %d Blue: %d\n", redValue, greenValue, blueValue);

  analogWrite(RGB_LED_RED_PIN_NUMBER, redValue);
  analogWrite(RGB_LED_GREEN_PIN_NUMBER, greenValue);
  analogWrite(RGB_LED_BLUE_PIN_NUMBER, blueValue);
  delay(1000);
}