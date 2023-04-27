int voice = 12; //Define the 12 pin input for the variable "voice"
int LED = 5;  //Define the 5 pin output for the variable "LED"

void setup() {

pinMode(voice, INPUT);  //Set the "voice" pin as an input.
pinMode(LED, OUTPUT);   //Set the "LED" pin as an output.

}

void loop() {

      if(digitalRead(voice) == 1){    //Checks if the digital signal received from the "voice" input pin is equal to 1. 
       digitalWrite(LED, 0);  //Turns off the LED connected to the "LED" output pin.
       delay(1000);  // Waits for 1 second
   }
   else{   // If the digital signal received from the "voice" input pin is not equal to 1.
  digitalWrite(LED, 1);  // Turns on the LED connected to the "LED" output pin.
 }
}
