from machine import Pin,I2C
import ssd1306
import machine
import time
i2c = I2C(scl=Pin(5), sda=Pin(4), freq=100000)      #Init i2c
lcd = ssd1306.SSD1306_I2C(128, 64, i2c)

trig = Pin(13,Pin.OUT, pull=None)
echo = Pin(12, Pin.IN, pull=None)
trig.value(0)
echo.value(0)

def send_pulse_and_wait(echo_timeout_us=500*2*30):
        trig.value(0) # Stabilize the sensor
        time.sleep_us(5)
        trig.value(1)
        # Send a 10us pulse.
        time.sleep_us(10)
        trig.value(0)
        try:
            pulse_time = machine.time_pulse_us(echo, 1, echo_timeout_us)
            return pulse_time
        except OSError as ex:
            if ex.args[0] == 110: # 110 = ETIMEDOUT
                raise OSError('Out of range')
            raise ex

def distance_cm():
        pulse_time = send_pulse_and_wait()
        cms = (pulse_time / 2) / 29.1
        return cms
 
def main():
  try:
    while True:
      distance = distance_cm()
      print(distance)
      lcd.fill(0)
      lcd.text("Distance:",30,20) 
      lcd.text(str(distance),30,40)
      lcd.show()
  except KeyboardInterrupt:
            pass

main()



