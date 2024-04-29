#include "ConnectGateway.h"

ConnectGateway::ConnectGateway(const char* gatewayName,const char* deviceName,uint16_t port){
  strcpy(_gatewayName,gatewayName);
  strcpy(_deviceName,deviceName);
  _connect_port = port;
}


bool ConnectGateway::begin(){
  if(!rp2040.isPicoW()){
    return false;
  }

  if(!udp){
    udp = new AsyncUDP();
  }

  if(udp->listen(_connect_port)){
    Serial.println("UDP connected");

    udp->onPacket([](AsyncUDPPacket packet)
    {
      if (memcmp((char*)packet.data(),_gatewayName,strlen(_gatewayName)) == 0){
        _gateway_ip = packet.remoteIP();
      }
    });
  }

  _lastCheck = millis();

  return true;
}

bool ConnectGateway::isConnected(){
  char  message[256];

  if (millis() - _lastCheck > CHACK_INTERVAL_MS){  
    if (!_connected){
      sprintf(message,"{\"gateway\":\"%s\",\"device\":\"%s\"}",_gatewayName,_deviceName);
      udp->broadcastTo(message,_connect_port);
    }
    _lastCheck = millis();
  }
  return _connected;
}

void ConnectGateway::disconnect(){
  _connected = false;
}

IPAddress ConnectGateway::getGatewayIp(){
  return isConnected() ? _gateway_ip : IPAddress(0,0,0,0);
}