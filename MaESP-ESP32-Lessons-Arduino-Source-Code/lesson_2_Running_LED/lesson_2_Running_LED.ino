const int ledPins[] = {15, 14, 13, 12}; //Create an array of Pin15,Pin14,Pin13,Pin12 leds
int n = 0;
void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(ledPins[i], OUTPUT);
    
  }
}
void loop() {
  n = (n + 1) % 4;    //The remainder sign % guarantees that n is between 0 and 3
  digitalWrite(ledPins[n], HIGH);  //The value of the NTH LED is high level,turn off
  delay(30);          //Delay of 30 milliseconds
  digitalWrite(ledPins[n], LOW);   //The value of the NTH LED is low level,turn on
  delay(30);          //Delay of 30 milliseconds
}
