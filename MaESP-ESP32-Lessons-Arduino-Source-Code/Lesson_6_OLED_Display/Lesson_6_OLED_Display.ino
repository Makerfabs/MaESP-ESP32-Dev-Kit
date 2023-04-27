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

void setup() {
  // put your setup code here, to run once:

    Serial.begin(115200);
    Wire.begin(I2C_SDA, I2C_SCL);
    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;); // Don't proceed, loop forever
    }
    display.clearDisplay();
    display.display(); 
}

void loop() {
    display.clearDisplay();
    display.setCursor(30, 10);
    display.setTextColor(WHITE);
    display.setTextSize(1);
    display.println("Makerfabs");
    display.setCursor(30, 25);
    display.setTextColor(WHITE);
    display.setTextSize(1);
    display.println("time:");
    display.setCursor(30, 40);
    display.setTextColor(WHITE);
    display.setTextSize(1);
    display.println("2019-12-5");
    
    display.display();

    delay(500);

}
