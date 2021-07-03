#include "LCDHelper.h"

LCDHelper::LCDHelper(uint8_t rs, uint8_t enable,
                     uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3) : lcd(rs, enable, d0, d1, d2, d3) {

    this->lcd.begin(LCD_COLS, LCD_ROWS);
    this->setUpSymbols();

}

void LCDHelper::setUpSymbols() {
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

    this->lcd.createChar(LCD_LOCKED_SYMBOL, lcdLockedSymbol);
    this->lcd.createChar(LCD_UNLOCKED_SYMBOL, lcdUnlockedSymbol);
    this->lcd.createChar(LCD_LOADING_SYMBOL, lcdLoadingSymbol);
    this->lcd.createChar(LCD_CHECK_SYMBOL, lcdCheckSymbol);
    this->lcd.home();
}

void LCDHelper::writeLocked() {
    this->lcd.clear();
    this->lcd.print("Locked!");
    this->lcd.write(static_cast<byte>(LCD_LOCKED_SYMBOL));
}

void LCDHelper::writeKnocks(const int& knocks) {
    this->lcd.clear();
    this->lcd.print("Locked!");
    this->lcd.write(static_cast<byte>(LCD_LOCKED_SYMBOL));
    this->lcd.print(" ");
    this->lcd.print(knocks);
    this->lcd.write(LCD_CHECK_SYMBOL);
}

void LCDHelper::writeUnlocked() {
    this->lcd.clear();
    this->lcd.print("Unlocked!");
    this->lcd.write(static_cast<byte>(LCD_UNLOCKED_SYMBOL));
}

void LCDHelper::writeUnlocking() {
    this->lcd.clear();
    this->lcd.print("Unlocking!");
    this->lcd.write(static_cast<byte>(LCD_LOADING_SYMBOL));
}

void LCDHelper::writeLocking() {
    this->lcd.clear();
    this->lcd.print("Locking!");
    this->lcd.write(static_cast<byte>(LCD_LOADING_SYMBOL));
}
