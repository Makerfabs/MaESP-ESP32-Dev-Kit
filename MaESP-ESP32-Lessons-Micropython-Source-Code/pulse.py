from machine import Pin,ADC
import machine
from micropython import const
import time
import ssd1306
import math

pscl = machine.Pin(5, machine.Pin.OUT)
psda = machine.Pin(4, machine.Pin.OUT)
i2c = machine.I2C(scl=pscl, sda=psda)
oled = ssd1306.SSD1306_I2C(128, 64, i2c)

counttime=0
try:
  while True:
    adc = ADC(Pin(32)) 			  #Create ADC object on ADC pin		
    adcValue=adc.read() 			  #read value, 0-4095 across voltage range 0.0v - 1.0v
    adc.atten(ADC.ATTN_11DB)       #set 11dB input attenuation (voltage range roughly 0.0v - 3.6v)
    adc.width(ADC.WIDTH_10BIT)    # set 10 bit return values
    adcValue=adc.read()              # read value using the newly configured attenuation and width
    oled.line(counttime,40,counttime,adcValue-420,1)   #Drew the heart rate
    oled.show()
    print(adcValue)
    time.sleep_ms(1)
    counttime+=1

    if(counttime>127):
      counttime=0
      oled.fill(0)                    #Clear the screen
      oled.show()
except KeyboardInterrupt:
      pass   
