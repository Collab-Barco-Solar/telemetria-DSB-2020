#!/usr/bin/env python

import serial
ser = serial.Serial('/dev/ttyACM0', 115200)
print(ser.name)

while(True):

	print(ser.readline())

ser.close()
