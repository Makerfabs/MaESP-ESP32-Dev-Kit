const int ledPin = 5;    //  set the led pin number

int frequency = 1000;    // set frequency to 5 kHz

void setup() {
  pinMode(ledPin, OUTPUT);    // set the led pin in OUTPUT mode
}

void loop() {
  for (int dutyCycle = 0; dutyCycle <= 1024; dutyCycle++) {   // dutyCycle cycles between 0 and 1024
    analogWrite(ledPin, dutyCycle);    // change the duty of led
    
    delay(2);   // adjust delay based on frequency and duty cycle
  }
}
