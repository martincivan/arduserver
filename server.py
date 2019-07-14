import psutil
import serial
import time
from mss import mss
import numpy as np
import cv2
import pyautogui



# print(psutil.cpu_percent())
# print(int(psutil.cpu_freq().current))
# print(psutil.virtual_memory())
# print(psutil.sensors_temperatures())
# print(psutil.sensors_fans()['nct6795'][1])

def bincount_app(a):
    a2D = a.reshape(-1,a.shape[-1])
    col_range = (256, 256, 256) # generically : a2D.max(0)+1
    a1D = np.ravel_multi_index(a2D.T, col_range)
    return np.unravel_index(np.bincount(a1D).argmax(), col_range)

port = '/dev/ttyUSB0'

ser = serial.Serial(port, 9600)

def posli():
    vystup = ""
    # vystup += str(int(psutil.cpu_freq().current))
    # vystup += chr(33)
    # vystup += str(int(psutil.sensors_temperatures()['k10temp'][0].current))
    # vystup += chr(33)
    # vystup += str(int(psutil.sensors_temperatures()['nct6795'][0].current))
    # vystup += chr(33)
    # vystup += str(psutil.sensors_fans()['nct6795'][1].current)
    # vystup += chr(33)
    # vystup += str(psutil.sensors_fans()['nct6795'][2].current)
    # vystup += chr(33)

    # shotter = mss()
    # pixels = shotter.grab((0, 0, 2560, 1440)).pixels
    # farby = [[[0]*256]*256]*256
    # for i in pixels:
    #     for j in i:
    #         farby[j[0]//1][j[1]//1][j[2]//1] += 1

    # najvacsie = 0
    # for (r, item) in enumerate(farby):
    #     for (g, item2) in enumerate(item):
    #         for (b, item3) in enumerate(item2):
    #             if item3 > najvacsie and (r != 0 and g != 0) and (r != 0 and b != 0) and (b != 0 and g != 0):
    #                 rn = r
    #                 bn = b
    #                 gn = g
    #                 najvacsie = item3
    vystup = vystup.encode()
    # print(str(rn)+ " " + str(gn)+ " "+ str(bn) + " " + str(najvacsie))

    image = pyautogui.screenshot()
    image = cv2.cvtColor(np.array(image), cv2.COLOR_RGB2BGR)
    nieco = bincount_app(image)

    vystup += bytes([nieco[0].item()])
    vystup += bytes([nieco[1].item()])
    vystup += bytes([nieco[2].item()])
    print(str(nieco[0].item()) + " " + str(nieco[1].item()) + " " + str(nieco[2].item()))
    ser.write(vystup)
    # print(vystup)
    ser.flush()

while True:
    ser.read()
    posli()
    # time.sleep(1)

ser.close()