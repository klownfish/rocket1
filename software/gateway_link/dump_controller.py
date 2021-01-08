import serial.tools.list_ports
import serial
import sys
from utils.definitions import *

def get_safe_devices():
        safeStrings = [
            "usb",
            "arduino",
            "ch340"
        ]
        safe_devices = []

        devices = serial.tools.list_ports.comports()

        for d in devices:
            flag = False
            for substring in safeStrings:
                if substring in d.description.lower():
                    flag = True
            if flag:
                safe_devices.append(d)

        return safe_devices

if not argv[1]:
    print("please specify where to save")
    sys.exit()
try:
    f = open(argv[1], "wb")
except:
    print("could not open file")

ser = serial.Serial(baudrate=BAUD, timeout=0.2)
devices = get_safe_devices()
for device in devices
    ser.port = devices
    ser.write(CONTROLLER_HANDSHAKE)
    if ser.read(1) == CONTROLLER_HANDSHAKE:
        break

ser.write(CONTROLLER_DUMP_FLASH)
print("dumping...")
while True:
    byte = ser.read(1)
    if byte == None:
        break
    f.write(byte)

print("done! dumped to ", argv[1])
print("open the file with the dashboard to parse")