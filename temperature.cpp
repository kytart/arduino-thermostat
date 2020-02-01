#include "temperature.h"
#include "config.h"

#define RECORD_TEMPERATURE_RESOURCE "/temperature"

String createRecordTemperatureJsonBodyString(int temperature) {
  return "{\"room\":\"" + String(ROOM) + "\",\"temperature\":" + String(temperature) + "}";
}

void recordTemperature(WiFiClient *wifiClient, int temperature) {
  int responseCode;
  String requestBody = createRecordTemperatureJsonBodyString(temperature);
  httpRequest(wifiClient, HTTP_POST, RECORD_TEMPERATURE_RESOURCE, requestBody, responseCode);
  if (responseCode == HTTP_OK) {
    Serial.println("Temperature recorded");
  } else {
    Serial.print("Temperature failed to record with response code ");
    Serial.println(responseCode);
  }
}
