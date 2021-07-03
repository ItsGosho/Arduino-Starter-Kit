#include <Arduino.h>
#include <Servo.h>
#include <LiquidCrystal.h>
#include "WrappedSerial.h"
#include "ArduinoUtils.h"
#include <avr8-stub.h>
#include "KnockChecker.h"
#include "LCDHelper.h"

//#define DEBUG

#ifdef DEBUG
#define DISABLE_SERIAL
#endif

#define BAUD_RATE 9600
#define SERVO_LOCKED_POSITION 90
#define SERVO_UNLOCKED_POSITION 0
#define SERVO_PIN 9
#define PIEZO_PIN A0
#define LOCK_BUTTON_PIN 8
#define YELLOW_LED_PIN 12
#define GREEN_LED_PIN 11
#define RED_LED_PIN 10
#define KNOCK_THRESHOLD_VALUE 10
#define UNLOCK_KNOCKS_REQUIRED 5
#define LCD_RS_PIN 7
#define LCD_EN_PIN 6
#define LCD_D0_PIN 5
#define LCD_D1_PIN 4
#define LCD_D2_PIN 3
#define LCD_D3_PIN 2
#define LCD_COLS 16
#define LCD_ROWS 1

//TODO: Спрямо предходният. То се води по тях когато получи Knock
const KnockTimingRequirement knockTimingRequirements[5] = {
        {-1,   -1},
        {1000, 5000},
        {0,    1000},
        {0,    1000},
        {1000, 5000}
};

bool isBoxLocked = true;
int numberOfKnocks = 0;
unsigned long lastKnockMS = 0;

Servo myServo;
LiquidCrystal lcd(LCD_RS_PIN, LCD_EN_PIN, LCD_D0_PIN, LCD_D1_PIN, LCD_D2_PIN, LCD_D3_PIN);
KnockChecker knockChecker; //TODO:

void lockBox() {
    LCDHelper::writeLocking(lcd);
    myServo.write(SERVO_LOCKED_POSITION);
    delay(450);

    isBoxLocked = true;
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(RED_LED_PIN, HIGH);
    numberOfKnocks = 0;
    WrappedSerial::println("The box is locked!");
    LCDHelper::writeLocked(lcd);
}

bool isKnockThresholdPassed(const int& value) {
    return value >= KNOCK_THRESHOLD_VALUE;
}

bool isKnockTimingPassed() {
    KnockTimingRequirement knockRequirement = knockTimingRequirements[numberOfKnocks];

    if (knockRequirement.minTimeMS == -1 && knockRequirement.maxTimeMS == -1)
        return true;

    unsigned long currentTime = millis();
    unsigned long timePassSinceLastKnock = currentTime - lastKnockMS;

    if (timePassSinceLastKnock < knockRequirement.minTimeMS || timePassSinceLastKnock > knockRequirement.maxTimeMS)
        return false;

    return true;
}

bool isKnocksEnough() {
    return numberOfKnocks >= UNLOCK_KNOCKS_REQUIRED;
}

void unlockBox() {
    LCDHelper::writeUnlocking(lcd);
    myServo.write(SERVO_UNLOCKED_POSITION);
    delay(450);

    isBoxLocked = false;
    digitalWrite(GREEN_LED_PIN, HIGH);
    digitalWrite(RED_LED_PIN, LOW);
    LCDHelper::writeUnlocked(lcd);
}

void tryUnlockBox(const int& piezoValue) {

    if (!isKnocksEnough()) {

        if (!isKnockThresholdPassed(piezoValue))
            return;

        if (!isKnockTimingPassed()) {
            lockBox();
            return;
        }

        ArduinoUtils::blinkLed(YELLOW_LED_PIN);
        numberOfKnocks++;
        LCDHelper::writeKnocks(lcd, numberOfKnocks);
        lastKnockMS = millis();
    }

    if (isKnocksEnough())
        unlockBox();
}

void setup() {

#ifdef DEBUG
    debug_init();
#endif

    myServo.attach(SERVO_PIN);
    lcd.begin(LCD_COLS, LCD_ROWS);

    byte lcdLockedSymbol[] = {
            B01110,
            B10001,
            B10001,
            B10001,
            B11111,
            B11011,
            B11111,
            B11111
    };

    byte lcdUnlockedSymbol[] = {
            B01110,
            B10001,
            B10000,
            B10000,
            B11111,
            B11011,
            B11111,
            B11111
    };

    byte lcdLoadingSymbol[] = {
            B00100,
            B01010,
            B10001,
            B10101,
            B10110,
            B10000,
            B01110,
            B00000
    };

    byte lcdCheckSymbol[] = {
            B00000,
            B00001,
            B00011,
            B10110,
            B11100,
            B01000,
            B00000,
            B00000
    };

    lcd.createChar(LCD_LOCKED_SYMBOL, lcdLockedSymbol);
    lcd.createChar(LCD_UNLOCKED_SYMBOL, lcdUnlockedSymbol);
    lcd.createChar(LCD_LOADING_SYMBOL, lcdLoadingSymbol);
    lcd.createChar(LCD_CHECK_SYMBOL, lcdCheckSymbol);
    lcd.home();

    const short outputPins[5] = {YELLOW_LED_PIN, RED_LED_PIN, GREEN_LED_PIN, LOCK_BUTTON_PIN};
    ArduinoUtils::setPinsMode(outputPins, OUTPUT);

    WrappedSerial::begin(BAUD_RATE);
    lockBox();
}

void loop() {

    if (!isBoxLocked) {
        bool isLockedButtonPressed = digitalRead(LOCK_BUTTON_PIN) == HIGH;

        if (isLockedButtonPressed)
            lockBox();
    }

    if (isBoxLocked) {
        int piezoValue = analogRead(PIEZO_PIN);

        tryUnlockBox(piezoValue);
    }
}