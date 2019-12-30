#!/usr/bin/env python
import serial

tx1 = serial.Serial('/dev/ttyACM0', 115200)
print(tx1.name)

while(True):

	print(tx1.readline().decode(), end='' )

tx1.close()
