#include "ConnectWifi.h"
#include "ConnectGateway.h"

ConnectWifi connect;
ConnectGateway connectGateway("gateway","light");

void setup() {
  Serial.begin(115200);
  connect.begin();
  connectGateway.begin();
}

void loop() {
  if(connect.isConnected()){
    if(connectGateway.isConnected()){
      Serial.printf("Connected:",connectGateway.getGatewayIp().toString().c_str());
      delay(10000);
    }
  }
}
