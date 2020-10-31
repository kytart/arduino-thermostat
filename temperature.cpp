#include <ArduinoMqttClient.h>
#include "temperature.h"
#include "config.h"

void recordTemperature(MqttClient *mqttClient, int temperature) {
  mqttClient->beginMessage(MQTT_TOPIC);
  mqttClient->print(temperature);
  mqttClient->endMessage();
}
