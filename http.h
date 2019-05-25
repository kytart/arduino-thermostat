#include "Arduino.h"

#define HTTP_OK 200

#define HTTP_POST "POST"

String httpRequest(WiFiClient *wifiClient, char method[], char resource[], const String body, int & statusCode);
