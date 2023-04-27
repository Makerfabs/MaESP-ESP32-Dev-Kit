#include <Wire.h> // include the Wire library for I2C communication
#include <Adafruit_SSD1306.h> // include the Adafruit SSD1306 library for OLED display control
#include <OneWire.h> // include the OneWire library for DallasTemperature sensor communication
#include <DallasTemperature.h> // include the DallasTemperature library for temperature measurement

#define SCREEN_WIDTH 128 // define the OLED display width in pixels
#define SCREEN_HEIGHT 64 // define the OLED display height in pixels
#define OLED_RESET -1    // define the OLED reset pin number (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3c // define the OLED screen address
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); // initialize the OLED display

#define I2C_SDA 4 // define the I2C SDA pin number
#define I2C_SCL 5 // define the I2C SCL pin number
OneWire oneWire(12); // initialize the OneWire object with data pin 12
DallasTemperature sensors(&oneWire); // initialize the DallasTemperature sensor object with the OneWire object

void setup() {
  Serial.begin (115200); // initialize serial communication at 115200 baud rate
  Wire.begin(I2C_SDA, I2C_SCL); // initialize I2C communication with the defined SDA and SCL pins
  
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) { // check if the OLED display was successfully initialized
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // if not, loop forever
  }
}

void loop() {
  sensors.requestTemperatures(); // send a request to the DallasTemperature sensor to measure temperature
  float temperature = sensors.getTempCByIndex(0); // read and store the temperature in degrees Celsius
  
  display.clearDisplay(); // clear the OLED display
  display.setTextSize(1); // set the text size to 1
  display.setTextColor(WHITE); // set the text color to white
  display.setCursor(10, 16); // set the cursor position to (10, 16)
  display.println("temperatures:"); // display the text "temperatures:"
  display.setCursor(24, 40); // set the cursor position to (24, 40)
  display.println(String(temperature)); // display the measured temperature as a string
  display.display(); // update the OLED display with the new text

  delay(1000); // wait for 1000 milliseconds before updating the temperature again
}
