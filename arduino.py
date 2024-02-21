import serial
import time

stepPerRevolution = 2048
def send_string(degree_str : str):
    s = serial.Serial('COM5', 9600, timeout=1)
    s.readline()
    
    while True:
        s.write("{}\r\n".format(degree_str).encode())
        line = s.readline()
        print(line.decode())
        
        if b"true" in line:
            break
        

if __name__ == "__main__":
    send_string(str(2001))
        
