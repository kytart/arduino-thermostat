#include "Arduino.h"
#include <SPI.h>
#include <WiFi101.h>
#include "http.h"
#include "config.h"

String httpRequest(WiFiClient *wifiClient, char method[], char resource[], const String body, int & statusCode) {
  Serial.print("Server request: ");
  Serial.print(method);
  Serial.print(" ");
  Serial.println(resource);
  Serial.println(body);

  if (wifiClient->connect(SERVER_HOST, SERVER_PORT)) {
    wifiClient->print(method);
    wifiClient->print(" ");
    wifiClient->print(resource);
    wifiClient->println(" HTTP/1.1");
    wifiClient->print("Host: ");
    wifiClient->println(SERVER_HOST);
    wifiClient->println("Content-Type: application/json");
    wifiClient->print("Content-Length: ");
    wifiClient->println(body.length());
    wifiClient->println("Connection: close");
    wifiClient->println();
    wifiClient->println(body);

    String response = "";

    // read the whole response into a string
    while(wifiClient->connected()) {
      while(wifiClient->available()) {
        response += (char) wifiClient->read();
      }
    }
    
    wifiClient->stop();

    // parse response status code
    int statusCodeStartIndex = 9;
    statusCode = response.substring(statusCodeStartIndex, statusCodeStartIndex + 3).toInt();

    // parse response body
    int bodyStartIndex = response.lastIndexOf("\r\n");
    String body = response.substring(bodyStartIndex);

    Serial.print("Response: ");
    Serial.print(statusCode);
    Serial.print(" ");
    Serial.println(body);
    
    return body;
  } else {
    Serial.println("connection failed");
  }

  wifiClient->stop();
  statusCode = 0;
  return "";
}
