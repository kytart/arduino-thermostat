#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "lcd.h"
#include "DHT.h"

#define DEGREE_SYMBOL_INDEX 0

uint8_t DEGREE_SYMBOL[] = { 0x06, 0x09, 0x09, 0x06, 0x00, 0x00, 0x00, 0x00 };

void initializeLCD(LiquidCrystal_I2C *lcd) {
    lcd->begin();
    lcd->backlight();
    lcd->createChar(DEGREE_SYMBOL_INDEX, DEGREE_SYMBOL);
}

void writeConnectingToWifi(LiquidCrystal_I2C *lcd) {
    lcd->clear();
    lcd->print("Connecting to");
    lcd->setCursor(0, 1);
    lcd->print(" WiFi...");
}

void writeCurrentStatusToLCD(LiquidCrystal_I2C *lcd, const int setDegreesCelsius, const float realDegreesCelsius) {
    lcd->clear();
    lcd->print("Set:  ");
    lcd->print(setDegreesCelsius);
    lcd->write(DEGREE_SYMBOL_INDEX);
    lcd->print("C");
    lcd->setCursor(0, 1);
    lcd->print("Real: ");
    if (isnan(realDegreesCelsius)) {
        lcd->print("--");
    } else {
        lcd->print((int) realDegreesCelsius);
    }
    lcd->write(DEGREE_SYMBOL_INDEX);
    lcd->print("C");
}
