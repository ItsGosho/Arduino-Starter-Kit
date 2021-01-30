#include <Arduino.h>
#include <SerialPrintF.h>

//For pin numbers we don't need anything more than 256 :D
const short RGB_LED_RED_PIN_NUMBER = 9;
const short RGB_LED_GREEN_PIN_NUMBER = 10;
const short RGB_LED_BLUE_PIN_NUMBER = 11;

const short PHOTORESISTOR_RED_PIN_NUMBER = A0;
const short PHOTORESISTOR_GREEN_PIN_NUMBER = A1;
const short PHOTORESISTOR_BLUE_PIN_NUMBER = A2;

void setup()
{
  Serial.begin(9600);

  pinMode(RGB_LED_RED_PIN_NUMBER, OUTPUT);
  pinMode(RGB_LED_GREEN_PIN_NUMBER, OUTPUT);
  pinMode(RGB_LED_BLUE_PIN_NUMBER, OUTPUT);
}

void loop()
{
  int redSensorValue = analogRead(PHOTORESISTOR_RED_PIN_NUMBER);
  delay(5);
  int greenSensorValue = analogRead(PHOTORESISTOR_GREEN_PIN_NUMBER);
  delay(5);
  int blueSensorValue = analogRead(PHOTORESISTOR_BLUE_PIN_NUMBER);

  serial_printf(Serial, "Raw Sensor Values  Red: %d Green: %d Blue: %d\n", redSensorValue, greenSensorValue, blueSensorValue);

  int redValue = redSensorValue / 4;
  int greenValue = greenSensorValue / 4;
  int blueValue = blueSensorValue / 4;

  serial_printf(Serial, "Mapped Sensor Values  Red: %d Green: %d Blue: %d\n", redValue, greenValue, blueValue);

  analogWrite(RGB_LED_RED_PIN_NUMBER, redValue);
  analogWrite(RGB_LED_GREEN_PIN_NUMBER, greenValue);
  analogWrite(RGB_LED_BLUE_PIN_NUMBER, blueValue);
  delay(1000);
}