#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1    // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3c // I2C address of the SSD1306 OLED display

// Initialize the SSD1306 OLED display object with the specified screen width, height, I2C bus, and reset pin
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define I2C_SDA 4 // Pin number for the I2C Serial Data (SDA) line
#define I2C_SCL 5 // Pin number for the I2C Serial Clock (SCL) line
#define TRIGGER_PIN 13 // Pin number for the ultrasonic sensor trigger
#define ECHO_PIN    12 // Pin number for the ultrasonic sensor echo

void setup() {
  Serial.begin(115200); // Initialize serial communication with a baud rate of 115200 bits per second
  Wire.begin(I2C_SDA, I2C_SCL); // Initialize the I2C bus with the specified SDA and SCL pins

  // If the SSD1306 OLED display fails to allocate memory, print an error message to the serial monitor and enter an infinite loop
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  pinMode(TRIGGER_PIN, OUTPUT); // Set the trigger pin as output
  pinMode(ECHO_PIN, INPUT); // Set the echo pin as input

  display.clearDisplay(); // Clear the OLED display
  display.display(); // Update the OLED display with the cleared buffer
}

void loop() {
  digitalWrite(TRIGGER_PIN, LOW); // Set the ultrasonic sensor trigger pin to low
  delayMicroseconds(2); // Wait for 2 microseconds
  digitalWrite(TRIGGER_PIN, HIGH); // Set the ultrasonic sensor trigger pin to high
  delayMicroseconds(10); // Wait for 10 microseconds
  digitalWrite(TRIGGER_PIN, LOW); // Set the ultrasonic sensor trigger pin to low again

  long duration = pulseIn(ECHO_PIN, HIGH); // Measure the time it takes for the echo signal to return
  float distance_cm = duration / 58; // Convert the duration to centimeters using the speed of sound

  Serial.print("Distance (cm): "); // Print a label to the serial monitor
  Serial.println(distance_cm); // Print the measured distance in centimeters to the serial monitor
  delay(500); 
  display.clearDisplay(); // Clear the OLED display
  display.setCursor(30, 20); // Set the cursor position to (30, 20)
  display.setTextColor(WHITE); // Set the text color to white
  display.setTextSize(1); // Set the text size to 1x
  display.println("Distance:"); // Print a label to the OLED display
  display.setCursor(30, 40); // Set the cursor position to (30, 40)
  display.setTextSize(1); // Set the text size to 1x
  display.println(distance_cm); // Print the measured distance in centimeters to the OLED display
  display.display(); // Update the OLED display with the new buffer

  delay(500); 
}
