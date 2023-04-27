#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1    // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3c
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define I2C_SDA 4
#define I2C_SCL 5

int counttime = 0;

void setup() {
  pinMode(32, INPUT);
  Serial.begin (115200);
    
  Wire.begin(I2C_SDA, I2C_SCL);
    if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
        for(;;); // Don't proceed, loop forever
 }
}

void loop() {
  int adcValue;
  adcValue = analogRead(32);        // read value, 0-4095 across voltage range 0.0v - 1.0v
  adcValue = map(adcValue, 0, 4095, 0, 1023);    // convert to 10-bit value
  display.drawLine(counttime, 40, counttime, adcValue-420, WHITE);   // drew the heart rate
  display.display();
  Serial.println(adcValue);
  delay(1);
  counttime++;

  if (counttime > 127) {
    counttime = 0;
    display.clearDisplay();              // clear the screen
    display.display();
  }
}
