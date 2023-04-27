import time                 #use the time class
from machine import Pin     #use the machine.Pin class
led=Pin(5,Pin.OUT)          #create LED object from pin5,Set Pin5 to output

try:
  while True:                 #repeat the following code
    led.value(1)              #turn off (Set high level)
    time.sleep(0.5)           #waiting for 0.5 seconds
    led.value(0)              #turn on  (Set low level)
    time.sleep(0.5)           #waiting for 0.5 seconds    
except KeyboardInterrupt:
          pass



