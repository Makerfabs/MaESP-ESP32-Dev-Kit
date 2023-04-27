from machine import Pin
import time

voice=Pin(12,Pin.IN)           
led=Pin(5,Pin.OUT)             

try:
  while True:
    if (voice.value() == 1):
      led.value(0)     
      time.sleep(1)
    else :
      led.value(1)
except KeyboardInterrupt:
       pass   




