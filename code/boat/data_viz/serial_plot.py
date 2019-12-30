#!/usr/bin/env python
import matplotlib.pyplot as plt
import numpy as np
import serial

tx1 = serial.Serial('/dev/ttyACM0', 115200)
print(tx1.name)

while(True):

	print(tx1.readline().decode(), end='' )

ser.close()
