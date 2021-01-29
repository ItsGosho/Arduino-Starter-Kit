#include <Arduino.h>
#include <SerialPrintF.h>

const int SERIAL_BAUD = 9600;
const int TEMP_SENSOR_PIN_NUMBER = A0;
const float TEMP_SENSOR_PIN_MAX_VOLTAGE = 5.0;
const int TEMP_SENSOR_OFFSET_VOLTAGE = 0.500;
const int ADC_MAX_RESOLUTION = 1024;
const int LED_PIN_NUMBERS[3] = {2, 3, 4};
const float BASELINE_TEMP = 20.0;
const int LOOP_DELAY_MS = 1000;

void setupPins(void);
float readTemperature(int);

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
  float miliVoltage = (sensorVal * (TEMP_SENSOR_PIN_MAX_VOLTAGE / ADC_MAX_RESOLUTION)) * 1000;
  float temperature = (miliVoltage - TEMP_SENSOR_OFFSET_VOLTAGE) / 10.0;

  serial_printf(Serial, "[Reading Temperature] Sensor Value: %d, mV: %0f, Degrees: %2f\n", sensorVal, miliVoltage, temperature);
  return temperature;
}