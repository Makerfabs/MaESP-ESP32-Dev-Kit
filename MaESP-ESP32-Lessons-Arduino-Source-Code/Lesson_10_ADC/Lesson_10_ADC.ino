#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1    // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3c // Communication address for the OLED screen
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#define I2C_SDA 4 // SDA pin for I2C communication
#define I2C_SCL 5 // SCL pin for I2C communication

const int analogInPin = 32; // Analog input pin for reading sensor data

void drawCircle(int x, int y, int r, int color, int fill=0); // Function to draw a circle on the OLED screen 

void setup() {
    Serial.begin(115200); // Begin serial communication
    Wire.begin(I2C_SDA, I2C_SCL); // Begin I2C communication
    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) { // Initialize the OLED screen
        Serial.println(F("SSD1306 allocation failed")); // If initialization fails, print an error message
        for (;;); // Don't proceed, loop forever
    }
    pinMode(analogInPin, INPUT); // Set analog input pin as input
    display.clearDisplay(); // Clear the OLED screen
    display.display(); // Display the cleared screen
}

void loop() {
  int adcValue = analogRead(analogInPin); // Read the analog value from the sensor
  float radius = ((float)adcValue / 4095.0) * 64.0; // Map the range of adc values to the range of circle radius (0-32)
  
  display.clearDisplay(); // Clear the OLED screen
  drawCircle(64, 32, (int)radius, WHITE, 1); // Draw a circle on the OLED screen with specified parameters
  display.display(); // Display the circle on the OLED screen

  delay(500); // Wait for 500 milliseconds            
}

void drawCircle(int x, int y, int r, int color, int fill) {  
  if (fill == 0) { // If fill parameter is 0, draw only the outline of the circle
    for (int i=x-r; i<=x+r; i++) {
      display.drawPixel(i, y-sqrt(r*r-(x-i)*(x-i)), color); // Draw the upper half of the circle
      display.drawPixel(i, y+sqrt(r*r-(x-i)*(x-i)), color); // Draw the lower half of the circle
    }
    for (int i=y-r; i<=y+r; i++) {
      display.drawPixel(x-sqrt(r*r-(y-i)*(y-i)), i, color); // Draw the left half of the circle
      display.drawPixel(x+sqrt(r*r-(y-i)*(y-i)), i, color); // Draw the right half of the circle
    }
  } 
  else { // If fill parameter is 1, fill the circle with color
    for (int i=x-r; i<=x+r; i++) {
      int a = sqrt(r*r-(x-i)*(x-i));
      display.drawFastVLine(i, y-a, a*2, color); // Fill the vertical column of pixels within the circle
    }
    for (int i=y-r; i<=y+r; i++) {
      int a = sqrt(r*r-(y-i)*(y-i));
      display.drawFastHLine(x-a, i, a*2, color); // Fill the horizontal row of pixels within the circle
    }
  }
}
