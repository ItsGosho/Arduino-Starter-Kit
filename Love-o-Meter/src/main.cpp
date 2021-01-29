#include <Arduino.h>

const int SERIAL_BAUD = 9600;
const int TEMP_SENSOR_PIN_NUMBER = A0;
const int LED_PIN_NUMBERS[3] = {2, 3, 4};
const float BASELINE_TEMP = 20.0;

void setupPins(void);

void setup()
{
  Serial.begin(SERIAL_BAUD);
  setupPins();
}

void setupPins()
{
  for (const int pinNumber : LED_PIN_NUMBERS)
  {
    Serial.println(pinNumber);
    pinMode(pinNumber, OUTPUT);
    digitalWrite(pinNumber, LOW);
  }
}

void loop()
{
  delay(10000);
  int sensorVal = analogRead(TEMP_SENSOR_PIN_NUMBER);
  Serial.print("Sensor Value: ");
  Serial.print(sensorVal);

  float voltage = (sensorVal / 1024.0) * 5.0;
  Serial.print(", Volts: ");
  Serial.print(voltage);
  Serial.print(", degrees C: ");
  float temperature = (voltage - .5) * 100;
  Serial.println(temperature);

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

  delay(1);
}