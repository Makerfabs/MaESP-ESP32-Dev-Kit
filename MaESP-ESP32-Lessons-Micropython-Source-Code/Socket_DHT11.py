#main.py
import network
import webrepl
import dht
import time
from machine import Pin

try:
  import usocket as socket
except:
  import socket

AUTH_OPEN = 0
AUTH_WEP = 1
AUTH_WPA_PSK = 2
AUTH_WPA2_PSK = 3
AUTH_WPA_WPA2_PSK = 4

SSID = "Makerfabs"
PASSWORD = "20160704"
sensor = dht.DHT11(Pin(14))

def read_sensor():
  global temp, temp_percentage, hum
  temp = temp_percentage = hum = 0
  try:
    sensor.measure()
    temp = sensor.temperature()
    hum = sensor.humidity()
    print(temp)
    print(hum)
    if (isinstance(temp, float) and isinstance(hum, float)) or (isinstance(temp, int) and isinstance(hum, int)):
      msg = (b'{0:3.1f},{1:3.1f}'.format(temp, hum))
      temp_percentage = (temp+6)/(40+6)*(100)
      hum = round(hum, 2)
      return(msg)
    else:
      return('Invalid sensor readings.')
  except OSError as e:
    return('Failed to read sensor.')

def web_page():

  html = """<html><head><meta name="viewport" content="width=device-width, initial-scale=1">
  <style>body{padding: 20px; margin: auto; width: 50%; text-align: center;}
  .progress{background-color: #F5F5F5;} .progress.vertical{position: relative;
  width: 25%; height: 60%; display: inline-block; margin: 20px;}
  .progress.vertical > .progress-bar{width: 100% !important;position: absolute;bottom: 0;}
  .progress-bar{background: linear-gradient(to top, #f5af19 0%, #f12711 100%);}
  .progress-bar-hum{background: linear-gradient(to top, #9CECFB 0%, #65C7F7 50%, #0052D4 100%);}
  p{position: absolute; font-size: 1.5rem; top: 50%; left: 50%; transform: translate(-50%, -50%); z-index: 5;}</style></head>
  <body><h1>Makerfabs DHT Sensor</h1><div class="progress vertical">
  <p>"""+str(temp)+"""C<p>
  <div role="progressbar" style="height: """+str(temp_percentage)+"""%;" class="progress-bar"></div></div><div class="progress vertical">
  <p>"""+str(hum)+"""%</p>
  <div role="progressbar" style="height: """+str(hum)+"""%;" class="progress-bar progress-bar-hum"></div></div></body></html>"""
  return html

def do_connect(ssid, psw):
    import network
    import time  

    wlan = network.WLAN(network.STA_IF)
    wlan.active(True)
    s = wlan.config("mac")
    mac = ('%02x:%02x:%02x:%02x:%02x:%02x').upper() %(s[0],s[1],s[2],s[3],s[4],s[5])
    print(" Local MAC:"+mac) #get mac
    wlan.connect(ssid, psw)
    if not wlan.isconnected():
        print('connecting to network...' + ssid)
        wlan.connect(ssid, psw)
    start = time.ticks_ms() # get millisecond counter
    while not wlan.isconnected():
        time.sleep(1) # sleep for 1 second
        if time.ticks_ms()-start > 20000:
            print("connect timeout!")
            break
    if wlan.isconnected():
        print('network config:', wlan.ifconfig())
    return wlan

def connect():
 do_connect(SSID,PASSWORD)

def app():
    connect()
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.bind(('', 80))
    s.listen(5)

    while True:
      conn, addr = s.accept()
      print('Got a connection from %s' % str(addr))
      request = conn.recv(1024)
      print('Content = %s' % str(request))
      sensor_readings = read_sensor()
      print(sensor_readings)
      response = web_page()
      conn.send('HTTP/1.1 200 OK\n')
      conn.send('Content-Type: text/html\n')
      conn.send('Connection: close\n\n')
      conn.sendall(response)
      conn.close()

app()






