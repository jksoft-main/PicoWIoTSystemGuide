#include <WiFi.h>
#include "ConnectWifi.h"
#include "ConnectGateway.h"

ConnectWifi connect;
ConnectGateway connectGateway("gateway","light");
WiFiClient client;
const int lightSensorPin = A2;
const int lightSensorThreshold = 500;

void setup() {
  Serial.begin(115200);
  connect.begin();
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
  if(connect.isConnected()){
    if(connectGateway.isConnected()){
      Serial.printf("Connected:%s\n",connectGateway.getGatewayIp().toString().c_str());
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
