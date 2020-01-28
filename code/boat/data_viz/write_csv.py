#!/usr/bin/env python
import serial
import csv

fieldnames = ["Campo1","Campo2","Campo3","Campo4"]

tx1 = serial.Serial("/dev/ttyACM0", 115200)
print(tx1.name)

with open("dados.csv", "w") as csv_file:
        csv_writer = csv.DictWriter(csv_file, fieldnames=fieldnames, delimiter=';' )
        csv_writer.writeheader()

while(True):
        with open("dados.csv", "a") as csv_file:
                '''csv_writer = csv.writer(csv_file , delimiter=';')
                read = tx1.readline().decode().strip()
                print(str(read))
                csv_writer.writerow(read)'''
                text =  tx1.readline().decode().strip() + '\n'
                csv_file.write( text )
                print(text, end = '')

tx1.close()

