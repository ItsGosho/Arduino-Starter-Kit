#include <Arduino.h>
#include "../lib/LiquidCrystal/src/LiquidCrystal.h"

/*
 *
 * VSS  - N/A
 * VDD  - N/A
 * V0   - N/A
 * RS   - 9
 * R/W  - N/A
 * E    - 8
 * DB0  -
 * DB1  -
 * DB2  -
 * DB3  -
 * DB4  - 5
 * DB5  - 4
 * DB6  - 3
 * DB7  - 2
 * LED+ - N/A
 * LED- - N/A
 *
 * TILT - 13
 *
 * */

LiquidCrystal lcd(9, 8, 5, 4, 3, 2);

const int switchPin = 13;
int switchState = 0;
int prevSwitchState = 0;
int reply;

void setup() {
    Serial.begin(9600);
    lcd.begin(16, 2);
    pinMode(switchPin, INPUT);
    lcd.print("Ask the:");
    lcd.setCursor(0, 1);
    lcd.print("Crystal Ball!");
    Serial.println("Setup finished!");
}

void loop() {
    switchState = digitalRead(switchPin);

    if (switchState != prevSwitchState) {
        if (switchState == LOW) {
            reply = random(8);
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("The ball says:");
            lcd.setCursor(0, 1);

            switch (reply) {
                case 0:
                    lcd.print("Yes");
                    break;
                case 1:
                    lcd.print("Most likely");
                    break;
                case 2:
                    lcd.print("Certainly");
                    break;
                case 3:
                    lcd.print("Outlook good");
                    break;
                case 4:
                    lcd.print("Unsure");
                    break;
                case 5:
                    lcd.print("Ask again");
                    break;
                case 6:
                    lcd.print("Doubtful");
                    break;
                case 7:
                    lcd.print("No");
                    break;
            }
        }

        prevSwitchState = switchState;
    }
}