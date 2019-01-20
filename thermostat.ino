#include <LiquidCrystal_I2C.h>
#include "lcd.h"

#define DEFAULT_DEGREES 20

#define BUTTON_DECREMENT_PIN 12
#define BUTTON_INCREMENT_PIN 11

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

int degreesCelsius = DEFAULT_DEGREES;
bool buttonDecrementDown = false;
bool buttonIncrementDown = false;

void setup()
{
	initializeLCD(&lcd);

  // Define pin as input and activate the internal pull-up resistor
  pinMode(BUTTON_DECREMENT_PIN, INPUT_PULLUP);
  pinMode(BUTTON_INCREMENT_PIN, INPUT_PULLUP);

  writeCurrentStatusToLCD(&lcd, degreesCelsius);
}

void loop()
{
	bool settingsChanged = handleButtons();
  if (settingsChanged) {
    writeCurrentStatusToLCD(&lcd, degreesCelsius);
  }
  delay(100);
}

bool handleButtons() {
  bool settingsChanged = false;
  bool isDecrementButtonPushed = isButtonPushed(BUTTON_DECREMENT_PIN);
  bool isIncrementButtonPushed = isButtonPushed(BUTTON_INCREMENT_PIN);
  
  if (isDecrementButtonPushed) {
    if (!buttonDecrementDown) {
      degreesCelsius--;
      buttonDecrementDown = true;
      settingsChanged = true;
    }
  } else {
    buttonDecrementDown = false;
  }

  if (isIncrementButtonPushed) {
    if (!buttonIncrementDown) {
      degreesCelsius++;
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
