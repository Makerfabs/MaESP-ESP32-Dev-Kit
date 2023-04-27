#include <Arduino.h>

int servoPin = 14; // SG90舵机控制引脚
int freq = 50; // PWM输出频率
int resolution = 8; // PWM输出分辨率

void setup() {
  Serial.begin(115200); // 初始化串口
  ledcSetup(0, freq, resolution); // 设置PWM通道0
  ledcAttachPin(servoPin, 0); // 将通道与对应的引脚连接
}

void loop() {
  for (int angle = 0; angle <= 180; angle ++) {
    int dutyCycle = map(angle, 0, 180, 0, 100); // 将角度映射至占空比
    ledcWrite(0, dutyCycle * 255 / 100); // 输出PWM，将占空比映射至0-255范围内
    Serial.printf("angle=%d,dutyCycle=%d\n", angle, dutyCycle);
    delay(20);
  }
}
