#include <WiFi.h>
#include "wifi.h"
#include <ArduinoMqttClient.h>
#include <Adafruit_BMP280.h>
#include "temperature.h"
#include "config.h"

#define BMP280_I2C_ADDRESS 0x76
#define DELAY 30 * 1000 // 1 minute in milliseconds

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);
Adafruit_BMP280 bmp;

void setup()
{
  Serial.begin(9600);
  while (!connectToWifi()) {
    Serial.println("Failed to connect to wifi");
    delay(10000);
  }

  while (!mqttClient.connect(MQTT_BROKER_HOST, MQTT_BROKER_PORT)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());
    delay(10000);
  }

  if (!bmp.begin(BMP280_I2C_ADDRESS)) {
    Serial.println("Could not find a valid BMP280 sensor, check wiring!");
    while (1);
  }
}

void loop()
{
  int temperature = bmp.readTemperature();
  int adjustedTemperature = temperature + SENSOR_ADJUST;
  recordTemperature(&mqttClient, adjustedTemperature);
  delay(DELAY);
}
