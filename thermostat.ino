#include <WiFi.h>
#include "wifi.h"
#include <ArduinoMqttClient.h>
#include <Adafruit_BMP280.h>
#include "temperature.h"
#include "config.h"

#define BMP280_I2C_ADDRESS 0x76
#define TIME_TO_SLEEP 2 * 60 * 1000000 // 2 minutes in microseconds

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);
Adafruit_BMP280 bmp;

void setup()
{
  Serial.begin(9600);
  if (!connectToWifi()) {
    Serial.println("Failed to connect to wifi");
    sleep();
  }

  if (!mqttClient.connect(MQTT_BROKER_HOST, MQTT_BROKER_PORT)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());
    while (1);
  }

  if (!bmp.begin(BMP280_I2C_ADDRESS)) {
    Serial.println("Could not find a valid BMP280 sensor, check wiring!");
    while (1);
  }
}

void loop()
{
  int temperature = bmp.readTemperature();
  recordTemperature(&mqttClient, temperature);
  delay(10000);
  sleep();
}

void sleep()
{
  Serial.println("go to sleep");
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP);
  esp_deep_sleep_start();
}
