#include <Arduino.h>
#include <Servo.h>

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

bool isKnockValueValid(int value) {

    if (value < KNOCK_THRESHOLD_VALUE) {
        return false;
    }

    digitalWrite(YELLOW_LED_PIN, HIGH);
    delay(100);
    digitalWrite(YELLOW_LED_PIN, LOW);

    return true;
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

bool isKnocksEnough() {
    return numberOfKnocks >= UNLOCK_KNOCKS_REQUIRED;
}

template<int S>
void setPinsMode(const short (& pins)[S], bool mode) {

    for (int i = 0; i < S; ++i)
        pinMode(pins[i], mode);
}

void setup() {
    myServo.attach(SERVO_PIN);

    const short outputPins[5] = {YELLOW_LED_PIN, RED_LED_PIN, GREEN_LED_PIN, LOCK_BUTTON_PIN};
    setPinsMode<5>(outputPins, OUTPUT);

    Serial.begin(BAUD_RATE);

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
            Serial.println("INCREMENTING!");
            numberOfKnocks++;
        }

        if (isKnocksEnough())
            unlockBox();
    }
}