import machine
import time

p14 = machine.Pin(14)
servo = machine.PWM(p14,freq=50)


try:
  for i in range(0, 180):  
      servo.duty(i) 
      time.sleep_ms(20) 
      
except KeyboardInterrupt:
       pass     





