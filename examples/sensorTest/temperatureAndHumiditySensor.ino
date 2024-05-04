#include <Wire.h>
#include "DHT.h"

DHT dht20(DHT20);

void setup() {
  // シリアルを初期化
  Serial.begin(115200);
  // I2Cを初期化
  Wire.setSDA(8);
  Wire.setSCL(9);
  Wire.begin();
  // センサを初期化
  dht20.begin();
}

void loop() {
  float sensorValue[2] = {0};
  // 温度と湿度を取得
  dht20.readTempAndHumidity(sensorValue);
  // シリアルで出力
  Serial.print(sensorValue[0]);
  Serial.print(",");
  Serial.println(sensorValue[1]);

  delay(1000);
}
