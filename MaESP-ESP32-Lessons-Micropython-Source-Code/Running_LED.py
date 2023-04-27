from machine import Pin
import time

#Create an array of Pin15,Pin14,Pin13,Pin12 leds
leds = [Pin(15,Pin.OUT),Pin(14,Pin.OUT),Pin(13,Pin.OUT),Pin(12,Pin.OUT)]
n=0

try:
  while True:
    n = (n+1)%4    		 #The remainder sign % guarantees that n is between 0 and 3
    leds[n].value(1)  	 #The value of the NTH LED is high level,turn off
    time.sleep_ms(30)	 #Delay of 30 milliseconds
    leds[n].value(0)  	 #The value of the NTH LED is low level,turn on
    time.sleep_ms(30)	 #Delay of 30 milliseconds
except KeyboardInterrupt:
          pass



