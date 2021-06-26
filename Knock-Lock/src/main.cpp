#include <Arduino.h>
#include <Servo.h>
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

#define DEBUG

#ifdef DEBUG
#define DISABLE_SERIAL
#endif

bool isKnockValueValid(int value) {

    if (value < KNOCK_THRESHOLD_VALUE)
        return false;

    return true;
}

void blinkYellowLed() {
    digitalWrite(YELLOW_LED_PIN, HIGH);
    delay(100);
    digitalWrite(YELLOW_LED_PIN, LOW);
}

void println(const char* text) {

#ifndef DISABLE_SERIAL
    Serial.println(text);
#endif
}

void lockBox() {
    isBoxLocked = true;
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(RED_LED_PIN, HIGH);
    myServo.write(90);
    println("The box is locked!");
    delay(1000);
}

void unlockBox() {
    isBoxLocked = false;
    myServo.write(0);
    delay(20);
    digitalWrite(GREEN_LED_PIN, HIGH);
    digitalWrite(RED_LED_PIN, LOW);
    println("The box is unlocked!");
    numberOfKnocks = 0;
}

bool isKnocksEnough() {
    return numberOfKnocks >= UNLOCK_KNOCKS_REQUIRED;
}

template<int S>
void setPinsMode(const short (& pins)[S], bool mode) {

    for (int i = 0; i < S; ++i)
        pinMode(pins[i], mode);
}

void setup() {

#ifdef DEBUG
    debug_init();
#endif

    myServo.attach(SERVO_PIN);

    const short outputPins[5] = {YELLOW_LED_PIN, RED_LED_PIN, GREEN_LED_PIN, LOCK_BUTTON_PIN};
    setPinsMode<5>(outputPins, OUTPUT);

#ifndef DISABLE_SERIAL
    Serial.begin(BAUD_RATE);
#endif

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

        if (!isKnocksEnough() && isKnockValueValid(piezoValue)) {
            blinkYellowLed();
            numberOfKnocks++;
        }

        if (isKnocksEnough())
            unlockBox();
    }
}