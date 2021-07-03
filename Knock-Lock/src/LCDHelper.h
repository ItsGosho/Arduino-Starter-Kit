#ifndef KNOCK_LOCK_LCDHELPER_H
#define KNOCK_LOCK_LCDHELPER_H

#include <Arduino.h>
#include <LiquidCrystal.h>

#define LCD_LOCKED_CHAR 0
#define LCD_UNLOCKED_CHAR 1
#define LCD_LOADING_CHAR 2


namespace LCDHelper {

    void writeLocked(LiquidCrystal liquidCrystal);
    void writeUnlocked(LiquidCrystal liquidCrystal);
    void writeUnlocking(LiquidCrystal liquidCrystal);
    void writeLocking(LiquidCrystal liquidCrystal);
}


#endif //KNOCK_LOCK_LCDHELPER_H
