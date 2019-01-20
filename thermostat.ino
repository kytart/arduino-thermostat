#include <LiquidCrystal_I2C.h>
#include "lcd.h"
#include "DHT.h"

#define DEFAULT_DEGREES 20

#define BUTTON_DECREMENT_PIN 12
#define BUTTON_INCREMENT_PIN 11

#define THERMO_PIN 10
#define THERMO_TYPE DHT11

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

DHT thermo(THERMO_PIN, THERMO_TYPE);
float realDegreesCelsius = 0;

int setDegreesCelsius = DEFAULT_DEGREES;
bool buttonDecrementDown = false;
bool buttonIncrementDown = false;

void setup()
{
	initializeLCD(&lcd);

  // Define pin as input and activate the internal pull-up resistor
  pinMode(BUTTON_DECREMENT_PIN, INPUT_PULLUP);
  pinMode(BUTTON_INCREMENT_PIN, INPUT_PULLUP);

  writeCurrentStatusToLCD(&lcd, setDegreesCelsius, realDegreesCelsius);
  thermo.begin();
}

void loop()
{
  bool settingsChanged = handleButtons();
  float newRealDegreesCelsius = thermo.readTemperature();
  if (newRealDegreesCelsius != realDegreesCelsius) {
    realDegreesCelsius = newRealDegreesCelsius;
    settingsChanged = true;
  }
  if (settingsChanged) {
    writeCurrentStatusToLCD(&lcd, setDegreesCelsius, realDegreesCelsius);
  }
  delay(100);
}

bool handleButtons() {
  bool settingsChanged = false;
  bool isDecrementButtonPushed = isButtonPushed(BUTTON_DECREMENT_PIN);
  bool isIncrementButtonPushed = isButtonPushed(BUTTON_INCREMENT_PIN);
  
  if (isDecrementButtonPushed) {
    if (!buttonDecrementDown) {
      setDegreesCelsius--;
      buttonDecrementDown = true;
      settingsChanged = true;
    }
  } else {
    buttonDecrementDown = false;
  }

  if (isIncrementButtonPushed) {
    if (!buttonIncrementDown) {
      setDegreesCelsius++;
      buttonIncrementDown = true;
      settingsChanged = true;
    }
  } else {
    buttonIncrementDown = false;
  }

  return settingsChanged;
}

bool isButtonPushed(int pin) {
  int buttonRead = digitalRead(pin);
  return buttonRead == LOW;
}
