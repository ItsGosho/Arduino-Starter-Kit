#include <Arduino.h>
#include <Servo.h>

Servo myServo;

const short PIEZO_PIN = A0;
const short LOCK_BUTTON_PIN = 8;
const short YELLOW_LED_PIN = 12;
const short GREEN_LED_PIN = 11;
const short RED_LED_PIN = 10;
const int KNOCK_THRESHOLD_VALUE = 10;

bool isBoxLocked = false;
int numberOfKnocks = 0;

bool isKnockValueValid(int value) {

    if (value > KNOCK_THRESHOLD_VALUE) {
        digitalWrite(YELLOW_LED_PIN, HIGH);
        delay(50);
        digitalWrite(YELLOW_LED_PIN, LOW);
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
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(RED_LED_PIN, HIGH);
    myServo.write(90);
    Serial.println("The box is locked!");
    delay(1000);
}

void unlockBox() {
    isBoxLocked = false;
    myServo.write(0);
    delay(20);
    digitalWrite(GREEN_LED_PIN, HIGH);
    digitalWrite(RED_LED_PIN, LOW);
    Serial.println("The box is unlocked!");
    numberOfKnocks = 0;
}

void setup() {
    myServo.attach(9);
    pinMode(YELLOW_LED_PIN, OUTPUT);
    pinMode(RED_LED_PIN, OUTPUT);
    pinMode(GREEN_LED_PIN, OUTPUT);
    pinMode(LOCK_BUTTON_PIN, INPUT);

    Serial.begin(9600);

    digitalWrite(GREEN_LED_PIN, HIGH);
    myServo.write(0);
    Serial.println("The box is unlocked!");
}

void loop() {

    if (!isBoxLocked) {
        bool isLockedButtonPressed = digitalRead(LOCK_BUTTON_PIN) == HIGH;

        if (isLockedButtonPressed)
            lockBox();
    }

    if (isBoxLocked) {
        int piezoValue = analogRead(PIEZO_PIN);

        if (numberOfKnocks < 3) {

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