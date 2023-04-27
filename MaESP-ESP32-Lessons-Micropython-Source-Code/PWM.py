from machine import Pin, PWM  
import time 

frequency = 5000      			#set frequency
led = PWM(Pin(5), frequency) 		#create PWM object from pin5,Set frequency

try:
  while True:
    for duty_cycle in range(0, 1024): 	#duty_cycle cycles between 0 and 1024
      led.duty(duty_cycle)      		#duty cycle size of LED lights 
      time.sleep_ms(2)             #delay of 2 ms
except KeyboardInterrupt:
          pass


