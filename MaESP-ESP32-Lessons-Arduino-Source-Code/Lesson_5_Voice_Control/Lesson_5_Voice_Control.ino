const int pwmPin = 12;// Define the PWM output pin for the siren


int dutyCycle = 0;// Set the initial duty cycle to 0


void ambulenceSiren() {
ledcWriteTone(0, 400); // Set the tone frequency to 400Hz
ledcWrite(0, 512); // Set the duty cycle to 50%
delay(500); // Wait for 500 milliseconds
ledcWriteTone(0, 800); // Increase the tone frequency to 800Hz
delay(500); // Wait for 500 milliseconds

}

void setup() {
ledcSetup(0, 400, 10); // Configure PWM channel 0 with a frequency of 400Hz and a resolution of 10 bits
ledcAttachPin(pwmPin, 0); // Attach the PWM output to the specified pin
}

void loop() {
ambulenceSiren(); // Call the function to generate the siren sound repeatedly in a loop
}
