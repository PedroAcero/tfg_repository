import serial

with serial.Serial('/dev/ttyUSB1', 57600, timeout=5) as ser:
    line = ser.readline()
    if not line:
        line = b'fallo'
    print(line.decode('utf-8'))
    print(line)
    # print(line.decode('ascii'))
    # print(line.decode("ascii"))
    # print(type(line))
