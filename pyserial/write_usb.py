import serial
ser = serial.Serial('/dev/ttyUSB0', 57600)

# ser.open()

print(ser.is_open)

data = b'hello'
print(data)

ser.write(data)


ser.close()
