#include <WiFi101.h>
#include <LiquidCrystal_I2C.h>
#include "wifi.h"
#include "lcd.h"
#include <Adafruit_BMP280.h>
#include "temperature.h"

#define DEFAULT_DEGREES 20

#define BUTTON_DECREMENT_PIN 12
#define BUTTON_INCREMENT_PIN 11

#define BMP280_I2C_ADDRESS 0x76

#define LOOP_DELAY 100
#define RECORD_TEMPERATURE_INTERVAL 60000

WiFiClient client;

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

Adafruit_BMP280 bmp;
float realDegreesCelsius = 0;

int setDegreesCelsius = DEFAULT_DEGREES;
bool buttonDecrementDown = false;
bool buttonIncrementDown = false;

int recordTemperatureDelayBuffer = 0;

void setup()
{
  Serial.begin(9600);

  initializeLCD(&lcd);

  // Define pin as input and activate the internal pull-up resistor
  pinMode(BUTTON_DECREMENT_PIN, INPUT_PULLUP);
  pinMode(BUTTON_INCREMENT_PIN, INPUT_PULLUP);

  writeConnectingToWifi(&lcd);
  connectToWifi();

  if (!bmp.begin(BMP280_I2C_ADDRESS)) {
    Serial.println("Could not find a valid BMP280 sensor, check wiring!");
    writeThermoSensorFailed(&lcd);
    while (1);
  }

  writeCurrentStatusToLCD(&lcd, setDegreesCelsius, realDegreesCelsius);
}

void loop()
{
  bool settingsChanged = handleButtons();
  float newRealDegreesCelsius = bmp.readTemperature();
  if (newRealDegreesCelsius != realDegreesCelsius) {
    realDegreesCelsius = newRealDegreesCelsius;
    settingsChanged = true;
  }
  if (settingsChanged) {
    writeCurrentStatusToLCD(&lcd, setDegreesCelsius, realDegreesCelsius);
  }
  if (recordTemperatureDelayBuffer > RECORD_TEMPERATURE_INTERVAL) {
    recordTemperatureDelayBuffer = 0;
    recordTemperature(&client, realDegreesCelsius, setDegreesCelsius);
  }
  recordTemperatureDelayBuffer += LOOP_DELAY;
  delay(LOOP_DELAY);
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
