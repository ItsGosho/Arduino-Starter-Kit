#include <Arduino.h>
#include <Servo.h>

Servo myServo;

const int piezo = A0;
const int switchPin = 8;
const int yellowLed = 12;
const int greenLed = 11;
const int redLed = 10;

const int quiteKnock = 10;
const int loudKnock = 100;

bool isBoxLocked = false;
int numberOfKnocks = 0;

bool isKnockValueValid(int value) {

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

void lockBox() {
    isBoxLocked = true;
    digitalWrite(greenLed, LOW);
    digitalWrite(redLed, HIGH);
    myServo.write(90);
    Serial.println("The box is locked!");
    delay(1000);
}

void unlockBox() {
    isBoxLocked = false;
    myServo.write(0);
    delay(20);
    digitalWrite(greenLed, HIGH);
    digitalWrite(redLed, LOW);
    Serial.println("The box is unlocked!");
    numberOfKnocks = 0;
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

    if (!isBoxLocked) {
        int switchValue = digitalRead(switchPin);

        if (switchValue == HIGH)
            lockBox();
    }

    if (isBoxLocked) {
        int piezoValue = analogRead(piezo);

        if (numberOfKnocks < 3 && piezoValue > 0) {

            if (isKnockValueValid(piezoValue)) {
                numberOfKnocks++;
            }

            Serial.print(3 - numberOfKnocks);
            Serial.println(" more knocks to go!");
        }

        if (numberOfKnocks >= 3) {
            unlockBox();
        }
    }
}