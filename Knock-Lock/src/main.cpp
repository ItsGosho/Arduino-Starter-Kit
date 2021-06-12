#include <Arduino.h>
#include <Servo.h>

Servo myServo;

const int piezo = A0;
const int switchPin = 8;
const int yellowLed = 12;
const int greenLed = 11;
const int redLed = 10;

int knockVal;
int switchVal;

const int quiteKnock = 10;
const int loudKnock = 100;

boolean isLocked = false;
int numberOfKnocks = 0;

boolean checkForKnock(int value) {

    if (value > quiteKnock && value < loudKnock) {
        digitalWrite(yellowLed, HIGH);
        delay(50);
        digitalWrite(yellowLed, LOW);
        Serial.print("Valid knock of value ");
        Serial.println(value);

        return true;
    } else {
        Serial.print("Bad knock value ");
        Serial.println(value);

        return false;
    }
}

void setup() {
    myServo.attach(9);
    pinMode(yellowLed, OUTPUT);
    pinMode(redLed, OUTPUT);
    pinMode(greenLed, OUTPUT);
    pinMode(switchPin, INPUT);

    Serial.begin(9600);

    digitalWrite(greenLed, HIGH);
    myServo.write(0);
    Serial.println("The box is unlocked!");
}

void loop() {

    if (isLocked == false) {
        switchVal = digitalRead(switchPin);

        if (switchVal == HIGH) {
            isLocked = true;
            digitalWrite(greenLed, LOW);
            digitalWrite(redLed, HIGH);
            myServo.write(90);
            Serial.println("The box is locked!");
            delay(1000);
        }
    }

    if (isLocked == true) {
        knockVal = analogRead(piezo);

        if (numberOfKnocks < 3 && knockVal > 0) {

            if (checkForKnock(knockVal) == true) {
                numberOfKnocks++;
            }

            Serial.print(3 - numberOfKnocks);
            Serial.println(" more knocks to go!");
        }

        if (numberOfKnocks >= 3) {
            isLocked = false;
            myServo.write(0);
            delay(20);
            digitalWrite(greenLed, HIGH);
            digitalWrite(redLed, LOW);
            Serial.println("The box is unlocked!");
            numberOfKnocks = 0;
        }
    }
}