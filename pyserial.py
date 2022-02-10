
import serial
ser = serial.Serial("/dev/cu.usbserial-1410", 115200, timeout=0.1) 


while True:
    print("type 0 ~ 9 to display number ")
    print("type 't' to show temperature")
    print("type 'h' to show humidity")
    command = input("type -1 to quit:")
    if (command=="-1"):break
    else:
        ser.write(command.encode('utf-8'))
    
ser.close()    