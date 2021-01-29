#include <Arduino.h>

const int TEMP_SENSOR_PIN_NUMBER = A0;
const float BASELINE_TEMP = 20.0;

void setupPins(void);

void setup()
{
  Serial.begin(9600);

  for (int pinNumber = 2; pinNumber < 5; pinNumber++)
  {
    pinMode(pinNumber, OUTPUT);
    digitalWrite(pinNumber, LOW);
  }
}

void setupPins() {
  
}

void loop()
{
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
  else if (temperature >= BASELINE_TEMP + 2 && temperature < BASELINE_TEMP  + 4)
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