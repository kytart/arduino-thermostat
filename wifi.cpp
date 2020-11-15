#include "Arduino.h"
#include <WiFi.h>
#include "wifi.h"
#include "config.h"

void printWiFiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

bool connectToWifi() {

  // attempt to connect to WiFi network:
  int status;
  Serial.print("Attempting to connect to SSID: ");
  Serial.println(WIFI_SSID);
  // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  // wait 30 seconds for connection:
  delay(10000);

  status = WiFi.status();

  if (status == WL_CONNECTED) {
    printWiFiStatus();
    return true;
  } else {
    return false;
  }
}
