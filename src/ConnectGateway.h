#ifndef ConnectGateway_h
#define ConnectGateway_h

#include <Arduino.h>
#include <WiFiUdp.h>

#define JSON_BUFFER_SIZE 256
#define DEFAULT_GATEWAY_NAME    "gateway"
#define DEFAULT_DEVICE_NAME     "device"
#define DEFAULT_CONNECT_PORT    1234
#define CHACK_INTERVAL_MS       1000L

class ConnectGateway {
public:
    ConnectGateway(const char* gatewayName=DEFAULT_GATEWAY_NAME,const char* deviceName=DEFAULT_DEVICE_NAME,uint16_t port=DEFAULT_CONNECT_PORT);
    bool begin();
    bool isConnected();
    void disconnect();
    IPAddress getGatewayIp();
private:
    IPAddress gateway_ip;
    WiFiUDP udp;
    bool connected = false;
    bool sent = false;
    char gatewayName[32];
    char deviceName[32];
    uint16_t connect_port;
    unsigned long lastCheck = 0;
};

#endif