#include <WiFi.h>
#include "ConnectGateway.h"

const char* ssid     = "ssid";
const char* password = "password";

const char* gatewayName = "gateway";
const char* locateName = "リビング";
const char* deviceName = "light";

ConnectGateway connectGateway(gatewayName,locateName,deviceName);
WiFiClient client;
const int lightSensorPin = A2;
const int lightSensorThreshold = 500;

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);

  connectGateway.begin();
}

bool getLight(){
  int lightSensorValue = analogRead(lightSensorPin);
  bool light = false;

  if(lightSensorValue > lightSensorThreshold) {
    light = true;
  }

  return light;
}

void loop() {
  if(WiFi.status() == WL_CONNECTED){
    if(connectGateway.isConnected()){
      if (!client.connect(connectGateway.getGatewayIp(), 61000)) {
        connectGateway.disconnect();
      }
      if (!client.connected()) {
        connectGateway.disconnect();
      }
      client.printf("{\"light\":%s}",getLight() ? "true" : "false");
      delay(10000);
    }
  }
}
