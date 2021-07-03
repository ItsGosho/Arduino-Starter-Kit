#include <Arduino.h>
#include <Servo.h>
#include "WrappedSerial.h"
#include "ArduinoUtils.h"
#include <avr8-stub.h>

Servo myServo;

const int BAUD_RATE = 9600;
const int SERVO_STARTING_POSITION = 0;
const short SERVO_PIN = 9;
const short PIEZO_PIN = A0;
const short LOCK_BUTTON_PIN = 8;
const short YELLOW_LED_PIN = 12;
const short GREEN_LED_PIN = 11;
const short RED_LED_PIN = 10;
const int KNOCK_THRESHOLD_VALUE = 10;
const int UNLOCK_KNOCKS_REQUIRED = 3;

bool isBoxLocked = false;
int numberOfKnocks = 0;

#ifdef DEBUG
#define DISABLE_SERIAL
#endif

bool isKnockValueValid(int value) {
    return value >= KNOCK_THRESHOLD_VALUE;
}

void lockBox() {

    myServo.write(90);
    delay(450);

    isBoxLocked = true;
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(RED_LED_PIN, HIGH);
    WrappedSerial::println("The box is locked!");
}

void unlockBox() {

    myServo.write(0);
    delay(450);

    isBoxLocked = false;
    digitalWrite(GREEN_LED_PIN, HIGH);
    digitalWrite(RED_LED_PIN, LOW);
    numberOfKnocks = 0;
    WrappedSerial::println("The box is unlocked!");
}

bool isKnocksEnough() {
    return numberOfKnocks >= UNLOCK_KNOCKS_REQUIRED;
}

void setup() {

#ifdef DEBUG
    debug_init();
#endif

    myServo.attach(SERVO_PIN);

    const short outputPins[5] = {YELLOW_LED_PIN, RED_LED_PIN, GREEN_LED_PIN, LOCK_BUTTON_PIN};
    ArduinoUtils::setPinsMode(outputPins, OUTPUT);

    WrappedSerial::begin(BAUD_RATE);

    digitalWrite(GREEN_LED_PIN, HIGH);
    myServo.write(SERVO_STARTING_POSITION);
}

void loop() {

    if (!isBoxLocked) {
        bool isLockedButtonPressed = digitalRead(LOCK_BUTTON_PIN) == HIGH;

        if (isLockedButtonPressed)
            lockBox();
    }

    if (isBoxLocked) {
        int piezoValue = analogRead(PIEZO_PIN);

        Serial.println(piezoValue);
        if (!isKnocksEnough() && isKnockValueValid(piezoValue)) {
            ArduinoUtils::blinkLed(YELLOW_LED_PIN);
            numberOfKnocks++;
        }

        if (isKnocksEnough())
            unlockBox();
    }
}