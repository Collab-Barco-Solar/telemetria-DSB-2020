#!/usr/bin/env python
import serial
import csv

fieldnames = ["Campo1","Campo2","Campo3"]

tx1 = serial.Serial("/dev/ttyACM0", 115200)
print(tx1.name)

with open("dados.csv", "w") as csv_file:
	csv_writer = csv.DictWriter(csv_file, fieldnames=fieldnames )
	csv_writer.writeheader()


while(True):
	
	with open("dados.csv", "a") as csv_file:
		csv_writer = csv.DictWriter(csv_file, fieldnames=fieldnames , delimiter=';')
		
		parse =  str(tx1.readline().decode().strip())
		print(parse)
		
		info = {
			"Campo1" : parse , #tx1.readline().decode()
			"Campo2" : "Text2",
			"Campo3" : "Text3"
		}
		
		csv_writer.writerow(info)
		

tx1.close()
