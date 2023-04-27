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

def circle(x,y,r,color,fill=0):
    if(fill==0):
            for i in range(x-r,x+r+1):
                oled.pixel(i,int(y-math.sqrt(r*r-(x-i)*(x-i))),color)
                oled.pixel(i,int(y+math.sqrt(r*r-(x-i)*(x-i))),color)
            for i in range(y-r,y+r+1):
                oled.pixel(int(x-math.sqrt(r*r-(y-i)*(y-i))),i,color)
                oled.pixel(int(x+math.sqrt(r*r-(y-i)*(y-i))),i,color)
    else:
            for i in range(x-r,x+r+1):
                a=int(math.sqrt(r*r-(x-i)*(x-i)))
                oled.vline(i,y-a,a*2,color)

            for i in range(y-r,y+r+1):
                a=int(math.sqrt(r*r-(y-i)*(y-i)))
                oled.hline(x-a,i,a*2,color)
                
try:
  while True:
    adc = ADC(Pin(32))				#Create ADC object on ADC pin	
    adcValue=adc.read()				#read value, 0-4095 across voltage range 0.0v - 1.0v
    adc.atten(ADC.ATTN_0DB)  #0dB attenuation, gives a maximum input voltage of 1v
    adc.width(ADC.WIDTH_12BIT) 	# set 12 bit return values, this is the default configuration
    adcValue=adc.read()				# read value using the newly configured attenuation and width
    time.sleep_ms(10)
    if(adc.read() == adcValue):
      oled.fill(0)
      circle(64,32,adcValue//64,1,1)    
      oled.show()
except KeyboardInterrupt:
      pass   








