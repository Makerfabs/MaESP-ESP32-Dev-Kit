from machine import Pin
import time

button=Pin(12,Pin.IN, pull=None)      #create Button object from pin12
led=Pin(5,Pin.OUT)       #create LED object from pin5,Set Pin5 to output 

try:
  while True:
    if(button.value() == 1):  #Press the button, the value is 1, release the button, the value is 0
      led.value(0)     	  #turn on
    else:
      led.value(1)  		  #turn off
except KeyboardInterrupt:
          pass






