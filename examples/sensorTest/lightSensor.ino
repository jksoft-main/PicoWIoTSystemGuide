#include <Wire.h>
#include <Digital_Light_TSL2561.h>

void setup() {
  // シリアルを初期化
  Serial.begin(115200);
  // I2Cを初期化
  Wire.setSDA(8);
  Wire.setSCL(9);
  Wire.begin();
  // センサを初期化
  TSL2561.init();
}

void loop() {
  // 可視光量を取得
  long lightSensorValue = TSL2561.readVisibleLux();
  // シリアルで出力
  Serial.println(lightSensorValue);
  delay(1000);
}
