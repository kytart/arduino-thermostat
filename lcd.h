#include <LiquidCrystal_I2C.h>

void initializeLCD(LiquidCrystal_I2C *lcd);
void writeConnectingToWifi(LiquidCrystal_I2C *lcd);
void writeCurrentStatusToLCD(LiquidCrystal_I2C *lcd, const int setDegreesCelsius, const float realDegreesCelsius);
