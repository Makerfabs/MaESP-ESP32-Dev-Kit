from machine import Pin,PWM
import time

pwm=PWM(Pin(12,Pin.OUT))


def ambulenceSiren(pwm):
    pwm.freq(400)          
    pwm.duty(512)
    time.sleep_ms(500)
    pwm.freq(800)
    time.sleep_ms(500)
   
try:
  while True:
      ambulenceSiren(pwm)    
except KeyboardInterrupt:
       pwm.deinit()
       pass     



