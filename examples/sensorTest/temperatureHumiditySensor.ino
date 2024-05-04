#include <Wire.h>
#include "DHT.h"

DHT dht20(DHT20);

void setup() {
  Serial.begin(115200);

  Wire.setSDA(8);
  Wire.setSCL(9);
  Wire.begin();
  dht20.begin();
}

void loop() {
  float sensorValue[2] = {0};

  if (!dht20.readTempAndHumidity(sensorValue)) {
    Serial.print("Humidity: ");
    Serial.print(sensorValue[0]);
    Serial.print(" %\t");
    Serial.print("Temperature: ");
    Serial.print(sensorValue[1]);
    Serial.println(" *C");
  } else {
    Serial.println("Failed to get temperature and humidity value.");
  }

  delay(1500);
}
