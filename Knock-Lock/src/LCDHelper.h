#ifndef KNOCK_LOCK_LCDHELPER_H
#define KNOCK_LOCK_LCDHELPER_H

#include <Arduino.h>
#include <LiquidCrystal.h>

#define LCD_LOCKED_SYMBOL 0
#define LCD_UNLOCKED_SYMBOL 1
#define LCD_LOADING_SYMBOL 2
#define LCD_CHECK_SYMBOL 3


namespace LCDHelper {

    void writeLocked(LiquidCrystal liquidCrystal);
    void writeKnocks(LiquidCrystal liquidCrystal, const int& knocks);
    void writeUnlocked(LiquidCrystal liquidCrystal);
    void writeUnlocking(LiquidCrystal liquidCrystal);
    void writeLocking(LiquidCrystal liquidCrystal);
}


#endif //KNOCK_LOCK_LCDHELPER_H
