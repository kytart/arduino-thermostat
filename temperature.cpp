#include "temperature.h"

#define RECORD_TEMPERATURE_RESOURCE "/temperature"

String createRecordTemperatureJsonBodyString(int current, int desired) {
  return "{\"current\":" + String(current) + ",\"desired\":" + String(desired) + "}";
}

void recordTemperature(WiFiClient *wifiClient, int current, int desired) {  
  int responseCode;
  String requestBody = createRecordTemperatureJsonBodyString(current, desired);
  httpRequest(wifiClient, HTTP_POST, RECORD_TEMPERATURE_RESOURCE, requestBody, responseCode);
  if (responseCode == HTTP_OK) {
    Serial.println("Temperature recorded");
  } else {
    Serial.print("Temperature failed to record with response code ");
    Serial.println(responseCode);
  }
}
