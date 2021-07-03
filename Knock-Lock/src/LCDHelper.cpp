#include "LCDHelper.h"


void LCDHelper::writeLocked(LiquidCrystal liquidCrystal) {
    liquidCrystal.clear();
    liquidCrystal.print("Locked!");
    liquidCrystal.write(static_cast<byte>(LCD_LOCKED_CHAR));
}

void LCDHelper::writeUnlocked(LiquidCrystal liquidCrystal) {
    liquidCrystal.clear();
    liquidCrystal.print("Unlocked!");
    liquidCrystal.write(static_cast<byte>(LCD_UNLOCKED_CHAR));
}

void LCDHelper::writeUnlocking(LiquidCrystal liquidCrystal) {
    liquidCrystal.clear();
    liquidCrystal.print("Unlocking!");
    liquidCrystal.write(static_cast<byte>(LCD_LOADING_CHAR));
}

void LCDHelper::writeLocking(LiquidCrystal liquidCrystal) {
    liquidCrystal.clear();
    liquidCrystal.print("Locking!");
    liquidCrystal.write(static_cast<byte>(LCD_LOADING_CHAR));
}
