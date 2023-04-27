from machine import Pin,I2C
import ssd1306

i2c = I2C(scl=Pin(5), sda=Pin(4), freq=100000)   #Init i2c
lcd=ssd1306.SSD1306_I2C(128,64,i2c)              #create LCD object,Specify col and row

try:
  lcd.text("Makerfabs",30,10)                    #set "Makerfabs" at (30,10)
  lcd.text("time:",30,25)                        #set "time:" at (30,25)
  lcd.text("2019-12-5",30,40)                    #set "2019-12-5" at (30,40)
  lcd.show()                                     #display
except KeyboardInterrupt:
          pass




