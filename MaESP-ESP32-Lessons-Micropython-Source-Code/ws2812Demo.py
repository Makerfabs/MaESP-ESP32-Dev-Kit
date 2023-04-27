import machine, neopixel 
import time

n = 12   #Define LED quantity
np = neopixel.NeoPixel(machine.Pin(12), n)   #Create the NeoPixe object

def demo(np):
    #n = np.n

    # Circular effect.One pixel runs through all strip positions, while the others are closed.
    for i in range(4 * n):
        for j in range(n):
            np[j] = (0, 0, 0)
        np[i % n] = (255, 255, 255)
        np.write()
        time.sleep_ms(25)

    #Rebound effect and set color (R,G,B), as well as wait time.
    #Wait time determines the speed of the bounce effect.
    for i in range(4 * n):
        for j in range(n):
            np[j] = (0, 0, 128)
        if (i // n) % 2 == 0:
            np[i % n] = (0, 0, 0)
        else:
            np[n - 1 - (i % n)] = (0, 0, 0)
        np.write()
        time.sleep_ms(60)
try:
  while True:
    demo(np)
except KeyboardInterrupt:
          pass
 






