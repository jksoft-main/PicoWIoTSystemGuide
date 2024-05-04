#include "ConnectGateway.h"

ConnectGateway::ConnectGateway(
  const char* _gatewayName,
  const char* _locationName,
  const char* _deviceName,
  uint16_t port
  ){
  strcpy(gatewayName,_gatewayName);
  strcpy(locationName,_locationName);
  strcpy(deviceName,_deviceName);
  connect_port = port;
}


bool ConnectGateway::begin(){
  if(!rp2040.isPicoW()){
    return false;
  }

  udp.begin(connect_port);

  lastCheck = millis();

  return true;
}

bool ConnectGateway::isConnected(){
  char  message[256];

  if (millis() - lastCheck > CHACK_INTERVAL_MS){  
    if (!connected){
      if (!sent){
        sprintf(message,"{\"gateway\":\"%s\",\"location\":\"%s\",\"device\":\"%s\"}",gatewayName,locationName,deviceName);
        udp.beginPacket(IPAddress(255,255,255,255), connect_port);
        udp.write(message);
        udp.endPacket();
        sent = true;
      }else{
        int packetSize = udp.parsePacket();
        if (packetSize) {
          int n = udp.read(message, 256);
          message[n] = 0;
          if (strcmp(message,gatewayName) == 0){
            gateway_ip = udp.remoteIP();
            connected = true;
          }
        }
        sent = false;
      }
    }
    lastCheck = millis();
  }
  return connected;
}

void ConnectGateway::disconnect(){
  connected = false;
}

IPAddress ConnectGateway::getGatewayIp(){
  return isConnected() ? gateway_ip : IPAddress(0,0,0,0);
}