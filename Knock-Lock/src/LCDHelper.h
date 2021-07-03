#ifndef KNOCK_LOCK_LCDHELPER_H
#define KNOCK_LOCK_LCDHELPER_H

#include <Arduino.h>
#include <LiquidCrystal.h>

#define LCD_LOCKED_SYMBOL 0
#define LCD_UNLOCKED_SYMBOL 1
#define LCD_LOADING_SYMBOL 2
#define LCD_CHECK_SYMBOL 3
#define LCD_COLS 16
#define LCD_ROWS 1

class LCDHelper {

private:
    LiquidCrystal lcd;

    void setUpSymbols();

public:
    LCDHelper(uint8_t rs, uint8_t enable,
              uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3);

    void writeLocked();

    void writeKnocks(const int& knocks);

    void writeUnlocked();

    void writeUnlocking();

    void writeLocking();
};

#endif //KNOCK_LOCK_LCDHELPER_H
