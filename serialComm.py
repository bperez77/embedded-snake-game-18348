import sys
import serial
import msvcrt

BR = 9600
#BR = 38400

def main():
	
	my_port = serial.Serial(port='COM1', baudrate=BR, bytesize=serial.EIGHTBITS,
							parity=serial.PARITY_NONE, 
                            stopbits=serial.STOPBITS_ONE,
							xonxoff=0, rtscts=0, timeout=0)

	print ("Port open is " + str(my_port.isOpen()))

	while True:
		try:
			char = msvcrt.getch()
		except:
			char = msvcrt.getwch()  # second call returns the actual key code
			continue
			
		print("Char is " + char)
		if(char=='q'):
			break
		else:
			my_port.write(char)
			
		print("Sent command")
	
	print("Terminating program")
	my_port.close()

if __name__ == "__main__":
	main()
    

