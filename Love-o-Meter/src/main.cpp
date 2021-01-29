#include <Arduino.h>
#include <SerialPrintF.h>

const int SERIAL_BAUD = 9600;
const int TEMP_SENSOR_PIN_NUMBER = A0;
const int LED_PIN_NUMBERS[3] = {2, 3, 4};
const float BASELINE_TEMP = 20.0;
const int LOOP_DELAY_MS = 1000;

void setupPins(void);
float readTemperature(int);
float convertAnalogReadToMiliVoltage(int);
float convertMiliVoltageToTemperature(int);

void setup()
{
  Serial.begin(SERIAL_BAUD);
  setupPins();
}

void setupPins()
{
  for (const int pinNumber : LED_PIN_NUMBERS)
  {
    pinMode(pinNumber, OUTPUT);
    digitalWrite(pinNumber, LOW);
  }
}

void loop()
{
  float temperature = readTemperature(TEMP_SENSOR_PIN_NUMBER);

  if (temperature < BASELINE_TEMP + 2)
  {
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
  }
  else if (temperature >= BASELINE_TEMP + 2 && temperature < BASELINE_TEMP + 4)
  {
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
  }
  else if (temperature >= BASELINE_TEMP + 6)
  {
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
  }

  delay(LOOP_DELAY_MS);
}

float readTemperature(int sensorPinNumber)
{
  int sensorVal = analogRead(TEMP_SENSOR_PIN_NUMBER);
  float miliVoltage = convertAnalogReadToMiliVoltage(sensorVal);
  float temperature = convertMiliVoltageToTemperature(miliVoltage);

  serial_printf(Serial, "[Reading Temperature] Sensor Value: %d, mV: %0f, Degrees: %2f\n", sensorVal, miliVoltage, temperature);
  return temperature;
}

//How to describe the 5.0 - Volts?!
//The maximum analogRead is 1023 (10 bit - 1)
float convertAnalogReadToMiliVoltage(int analogRead)
{
  return analogRead * (5.0 / 1024.0) * 1000;
}

float convertMiliVoltageToTemperature(int mV)
{
  return (mV - 500.0) / 10;
}