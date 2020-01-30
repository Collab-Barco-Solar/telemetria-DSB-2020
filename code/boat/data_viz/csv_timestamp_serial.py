#!/usr/bin/env python
import serial
import csv
import time

fieldnames = ["Latitude"," Longitude "," Speed(knots)"," DMS "," Reverse "," Motor "," Cruise "," Battery Current "," Potentiometer "," PV Modules "," Aux Battery "," Main Battery "," LC "," RC "," Left Pump "," Right Pump "," Motor Current"]

ts = time.gmtime()
print(time.strftime("%Y-%m-%d %H:%M:%S", ts))

filename = time.strftime("%Y-%m-%d_%H-%M-%S.csv", ts)

tx1 = serial.Serial("/dev/ttyUSB0", 2000000)
print(tx1.name)

with open(filename, "w") as csv_file:
        csv_writer = csv.DictWriter(csv_file, fieldnames=fieldnames, delimiter="," )
        csv_writer.writeheader()

while(True):


        with open(filename, "a") as csv_file:

            '''csv_writer = csv.writer(csv_file , delimiter='","')
            read = tx1.readline().decode().strip()
            print(str(read))
            csv_writer.writerow(read)'''
            
             
            text =  tx1.readline().decode().strip() + '\n'
            csv_file.write( text )
            print(text, end = '')
            
    
tx1.close()
