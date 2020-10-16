#include <WiFi.h>
#include "wifi.h"
#include <Adafruit_BMP280.h>
#include "temperature.h"

#define BMP280_I2C_ADDRESS 0x76
#define TIME_TO_SLEEP 2 * 60 * 1000000 // 2 minutes in microseconds

WiFiClient client;
Adafruit_BMP280 bmp;

void setup()
{
  Serial.begin(9600);
  connectToWifi();

  if (!bmp.begin(BMP280_I2C_ADDRESS)) {
    Serial.println("Could not find a valid BMP280 sensor, check wiring!");
    while (1);
  }
}

void loop()
{
  int temperature = bmp.readTemperature();
  recordTemperature(&client, temperature);
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP);
  esp_deep_sleep_start();
}
