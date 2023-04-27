const int button = 12; 
const int led = 5; 
void setup() {
  pinMode(button, INPUT_PULLUP); //Set the key pin to input mode and turn on the internal pull-up resistor
  pinMode(led, OUTPUT); //Set the LED pin to output mode
}
void loop() {
  if (digitalRead(button) == LOW) { //Detects whether a key is pressed?
    digitalWrite(led, HIGH); 
  } else {
    digitalWrite(led, LOW); 
  }
}
