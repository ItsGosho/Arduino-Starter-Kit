#include <Arduino.h>
#include <Servo.h>
#include "WrappedSerial.h"
#include "ArduinoUtils.h"
#include <avr8-stub.h>
#include "KnockChecker.h"

Servo myServo;
KnockChecker knockChecker;

const int BAUD_RATE = 9600;
const int SERVO_STARTING_POSITION = 0;
const short SERVO_PIN = 9;
const short PIEZO_PIN = A0;
const short LOCK_BUTTON_PIN = 8;
const short YELLOW_LED_PIN = 12;
const short GREEN_LED_PIN = 11;
const short RED_LED_PIN = 10;
const int KNOCK_THRESHOLD_VALUE = 10;
const int UNLOCK_KNOCKS_REQUIRED = 5;

//TODO: Спрямо предходният. То се води по тях когато получи Knock
const KnockRequirement knockRequirements[5] = {
        {-1, -1},
        {1000,5000},
        {0,1000},
        {0,1000},
        {1000,5000}
};

bool isBoxLocked = false;
int numberOfKnocks = 0;
unsigned long lastKnockMS = 0;

//#define DEBUG

#ifdef DEBUG
#define DISABLE_SERIAL
#endif

//ToDO: MAKE IT Locked by default

void lockBox() {

    myServo.write(90);
    delay(450);

    isBoxLocked = true;
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(RED_LED_PIN, HIGH);
    numberOfKnocks = 0;
    WrappedSerial::println("The box is locked!");
}

bool isKnockValueValid(int value) {

    if(value < KNOCK_THRESHOLD_VALUE)
        return false;

    int knockAttempt = numberOfKnocks + 1;
    //Ако няма такъв index директно пускам
    KnockRequirement knockRequirement = knockRequirements[knockAttempt - 1];

    if(knockRequirement.minTimeMS == -1 && knockRequirement.maxTimeMS == -1)
        return true;

    unsigned long currentTime = millis();
    unsigned long timePassSinceLastKnock = currentTime - lastKnockMS;

    if(timePassSinceLastKnock < knockRequirement.minTimeMS || timePassSinceLastKnock > knockRequirement.maxTimeMS) {
        Serial.println("Requirements not passed: min, max");
        Serial.println(knockRequirement.minTimeMS);
        Serial.println(knockRequirement.maxTimeMS);
        Serial.println("Instead times were: current, lastKnock, time passed (compared value)");
        Serial.println(currentTime);
        Serial.println(lastKnockMS);
        Serial.println(timePassSinceLastKnock);
        lockBox();
        return false;
    }

    return true;
}

void unlockBox() {

    myServo.write(0);
    delay(450);

    isBoxLocked = false;
    digitalWrite(GREEN_LED_PIN, HIGH);
    digitalWrite(RED_LED_PIN, LOW);
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

        if (!isKnocksEnough() && isKnockValueValid(piezoValue)) {
            ArduinoUtils::blinkLed(YELLOW_LED_PIN);
            numberOfKnocks++;
            Serial.println(numberOfKnocks);
            lastKnockMS = millis();
        }

        if (isKnocksEnough())
            unlockBox();
    }
}