#include "LCDHelper.h"


void LCDHelper::writeLocked(LiquidCrystal liquidCrystal) {
    liquidCrystal.clear();
    liquidCrystal.print("Locked!");
    liquidCrystal.write(static_cast<byte>(LCD_LOCKED_SYMBOL));
}

void LCDHelper::writeKnocks(LiquidCrystal liquidCrystal, const int& knocks) {
    liquidCrystal.clear();
    liquidCrystal.print("Locked!");
    liquidCrystal.write(static_cast<byte>(LCD_LOCKED_SYMBOL));
    liquidCrystal.print(" ");
    liquidCrystal.print(knocks);
    liquidCrystal.write(LCD_CHECK_SYMBOL);
}

void LCDHelper::writeUnlocked(LiquidCrystal liquidCrystal) {
    liquidCrystal.clear();
    liquidCrystal.print("Unlocked!");
    liquidCrystal.write(static_cast<byte>(LCD_UNLOCKED_SYMBOL));
}

void LCDHelper::writeUnlocking(LiquidCrystal liquidCrystal) {
    liquidCrystal.clear();
    liquidCrystal.print("Unlocking!");
    liquidCrystal.write(static_cast<byte>(LCD_LOADING_SYMBOL));
}

void LCDHelper::writeLocking(LiquidCrystal liquidCrystal) {
    liquidCrystal.clear();
    liquidCrystal.print("Locking!");
    liquidCrystal.write(static_cast<byte>(LCD_LOADING_SYMBOL));
}
