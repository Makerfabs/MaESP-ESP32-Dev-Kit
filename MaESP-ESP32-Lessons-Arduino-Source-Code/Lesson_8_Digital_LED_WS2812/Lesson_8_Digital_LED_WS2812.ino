#include <Adafruit_NeoPixel.h>

// Define the pin number that the LED strip is attached to and the number of LEDs in the strip
#define LED_PIN 12
#define NUM_LEDS 12

// Create an instance of the Adafruit_NeoPixel class with the specified number of LEDs and pin number
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

// Set up the LED strip by initializing it and showing the initial state (all LEDs off)
void setup() {
strip.begin();
strip.show();
}

// Continuously run the demo function in a loop
void loop() {
demo();
}

// A custom function to create a circular effect and a rebound effect on the LED strip
void demo() {

// Circular effect: One pixel runs through all strip positions while the others are closed.
for (int i = 0; i < 4 * NUM_LEDS; i++) { // Loop through four times the total number of LEDs
for (int j = 0; j < NUM_LEDS; j++) { // Turn off all LEDs except for the current one being lit
strip.setPixelColor(j, 0, 0, 0);
        }
strip.setPixelColor(i % NUM_LEDS, 255, 255, 255); // Set the color of the current LED
strip.show(); // Show the updated LED state
       delay(25); // Wait for a short period of time to create a smooth animation
}

// Rebound effect: The light bounces back and forth across the strip, changing color with each bounce.
// The wait time determines the speed of the bouncing effect.
for (int i = 0; i < 4 * NUM_LEDS; i++) { // Loop through four times the total number of LEDs
for (int j = 0; j < NUM_LEDS; j++) { // Set all LEDs to a dark blue color
     strip.setPixelColor(j, 0, 0, 128);
                            }
if ((i / NUM_LEDS) % 2 == 0) { // If the current bounce is going right
     strip.setPixelColor(i % NUM_LEDS, 0, 0, 0); // Turn off the current LED
                          } 
else { // Else, the current bounce is going left
     strip.setPixelColor(NUM_LEDS - 1 - (i % NUM_LEDS), 0, 0, 0); // Turn off the mirror LED on the other end of the strip
       }
     strip.show(); // Show the updated LED state
      delay(60); // Wait for a longer period of time to create a slower bouncing effect
       }
}
