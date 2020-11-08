#include <ArduinoMqttClient.h>
#include "temperature.h"
#include "config.h"

void recordTemperature(MqttClient *mqttClient, int temperature) {
  Serial.print("record temperature: ");
  Serial.println(temperature);
  mqttClient->beginMessage(MQTT_TOPIC);
  mqttClient->print(temperature);
  mqttClient->endMessage();
}
