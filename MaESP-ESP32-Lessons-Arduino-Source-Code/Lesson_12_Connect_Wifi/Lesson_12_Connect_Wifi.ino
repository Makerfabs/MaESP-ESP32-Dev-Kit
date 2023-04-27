#include <WiFi.h>

const char* ssid = "Makerfabs";    // Local network name
const char* password = "20160704"; // Local network password

void setup() {
Serial.begin(115200);    // Initialize serial communication at baud rate 115200
WiFi.mode(WIFI_STA);     // Set WiFi mode to station (client)
WiFi.begin(ssid, password);   // Connect to WiFi network using given SSID and password

while (WiFi.status() != WL_CONNECTED) {   // Wait until connection is established
delay(1000);
Serial.println("Connecting to WiFi...");
}

Serial.println("WiFi connected");          // Print message once WiFi is connected
Serial.print("IP address: ");

Serial.println(WiFi.localIP());            // Print the IP address obtained from DHCP server
}

void loop() {
// put your main code here, to run repeatedly:
}
