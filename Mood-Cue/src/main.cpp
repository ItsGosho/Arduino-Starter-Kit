#include <Arduino.h>
#include <Servo.h>
#include <SerialPrintF.h>

Servo servoMotor;

const short POTENTIOMETER_PIN_NUMBER = A0;
const short SERVO_MOTOR_PIN_NUMBER = 9;
const int SERIAL_BAUD = 9600;

void setup()
{
    Serial.begin(SERIAL_BAUD);

    servoMotor.attach(SERVO_MOTOR_PIN_NUMBER);
}

void loop()
{
    int potentiometerValue = analogRead(POTENTIOMETER_PIN_NUMBER);
    int servoAngle = map(potentiometerValue, 0, 1023, 0, 179);

    serial_printf(Serial, "\nPotentiometer Value: %d, Servo Angle: %d", potentiometerValue, servoAngle);

    servoMotor.write(servoAngle);
    delay(15);
}