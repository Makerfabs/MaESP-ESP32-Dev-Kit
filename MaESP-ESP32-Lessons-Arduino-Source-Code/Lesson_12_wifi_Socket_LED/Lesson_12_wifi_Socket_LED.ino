#include <WiFi.h>
#include <WebServer.h>// Include necessary libraries

const char* ssid = "Makerfabs";
const char* password = "20160704";

WebServer server(80);// Initialize a WebServer object on port 80
int ledPin = 5;
bool ledState = LOW;

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);// Set the LED pin as an output and set its initial state
  digitalWrite(ledPin, ledState);

  WiFi.begin(ssid, password);// Connect to the WiFi network using the provided credentials
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.print("Connected to WiFi, IP address: ");// Print the IP address assigned to the device by the router
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, [](){  // Generate an HTML response with two buttons to turn the LED on and off
    String html = "<html><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"></head>";
    html += "<body><h1>Makerfabs Web Server</h1><a href=\"/on\"><button>ON</button></a>&nbsp;";
    html += "<a href=\"/off\"><button>OFF</button></a></body></html>";
    server.send(200, "text/html", html);
  });

  server.on("/on", HTTP_GET, [](){  // Turn the LED on and update its state
    ledState = LOW;
    digitalWrite(ledPin, ledState);
    server.sendHeader("Location", "/");
    server.send(303);
  });

  server.on("/off", HTTP_GET, [](){  // Turn the LED off and update its state
    ledState = HIGH;
    digitalWrite(ledPin, ledState);
    server.sendHeader("Location", "/");
    server.send(303);
  });

  server.begin();
}

void loop() {
  server.handleClient();// Handle incoming client requests
}
