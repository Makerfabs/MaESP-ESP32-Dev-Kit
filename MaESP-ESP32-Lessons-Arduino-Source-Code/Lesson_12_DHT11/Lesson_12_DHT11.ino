#include"DHT.h"

#define DHTTYPE DHT11 
#define DHTPIN 14  

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  dht.begin();
  
}

void loop() {
  // put your main code here, to run repeatedly:
   delay(2000);
   float humidity = dht.readHumidity();
   float temperature = dht.readTemperature();


   Serial.print("Humidity:");
   Serial.print(humidity);
   Serial.print("%\t");
   Serial.print("Temperature:");
   Serial.print(temperature);
   Serial.print("°C\n");
  
}
