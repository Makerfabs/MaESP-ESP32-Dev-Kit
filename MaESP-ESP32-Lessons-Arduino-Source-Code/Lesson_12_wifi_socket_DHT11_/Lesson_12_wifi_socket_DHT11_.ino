#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include "DHT.h"

const char* ssid = "Makerfabs";
const char* password = "20160704";

#define DHTPIN 14
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

WebServer server(80);

float temp, hum;
String webPage;

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");// Print a message indicating a successful connection to the WiFi network
// Define the behavior of the root URL ("/") when accessed with an HTTP GET request
  server.on("/", handleRoot);

  server.begin();
  Serial.print("Server address: ");
  Serial.println(WiFi.localIP()); 
}

void loop() {
  // Handle incoming client requests
  server.handleClient();
// Read the temperature and humidity values from the DHT sensor
  readSensor();
}
// Generate an HTML response with two progress bars showing the temperature and humidity readings
void handleRoot() {
  // Generate an HTML response with two progress bars showing the temperature and humidity readings
  String html = "<html><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
  html += "<style>body{padding: 20px; margin: auto; width: 50%; text-align: center;}";
  html += ".progress{background-color: #F5F5F5;} .progress.vertical{position: relative;";
  html += "width: 25%; height: 60%; display: inline-block; margin: 20px;}";
  html += ".progress.vertical > .progress-bar{width: 100% !important;position: absolute;bottom: 0;}";
  html += ".progress-bar{background: linear-gradient(to top, #f5af19 0%, #f12711 100%);}";
  html += ".progress-bar-hum{background: linear-gradient(to top, #9CECFB 0%, #65C7F7 50%, #0052D4 100%);}";
  html += "p{position: absolute; font-size: 1.5rem; top: 50%; left: 50%; transform: translate(-50%, -50%); z-index: 5;}</style></head>";
  html += "<body><h1>Makerfabs DHT Sensor</h1><div class=\"progress vertical\">";
  html += "<p>" + String(temp) + " C<p>";
  html += "<div role=\"progressbar\" style=\"height: " + String((temp+6)/(40+6)*(100)) + "%;\" class=\"progress-bar\"></div></div><div class=\"progress vertical\">";
  html += "<p>" + String(hum) + "%</p>";
  html += "<div role=\"progressbar\" style=\"height: " + String(hum) + "%;\" class=\"progress-bar progress-bar-hum\"></div></div></body></html>";

  server.send(200, "text/html", html);// Send the HTML response with a status code of 200 (OK)
}

void readSensor() {
  temp = hum = 0;

  delay(2000);

  dht.begin();

  float tempRead = dht.readTemperature();
  float humRead = dht.readHumidity();

  if (isnan(tempRead) || isnan(humRead)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
// Update the temperature and humidity variables
  temp = tempRead;
  hum = humRead;
// Print the temperature and humidity readings to the serial monitor
  Serial.println("Temperature: " + String(temp) + " °C");
  Serial.println("Humidity: " + String(hum) + "%");
}
