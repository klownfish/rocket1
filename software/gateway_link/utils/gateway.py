from collections import defaultdict
from utils.data_handling import Timeseries, write_data_db
from utils.definitions import *
from utils.decoding import Decoder
from threading import Thread
from utils.decoding import bytes_to_int
import serial
import time
import serial.tools.list_ports

messages = {}

class Gateway():
    def __init__(self, influx):
        self.data = defaultdict(Timeseries)
        self.influx = influx
        self.time = 0

        self.ser = serial.Serial(timeout = 0.2) 
        self.stream = None

        self.stream_initialized = False
        self.serial_initialized = False
        self.exit = False
        self.is_live = False

        self.decoders = messages
        t = Thread(target=self.reader_from_stream)
        t.start()

    def get_time(self):
        return self.time

    def stop(self):
        self.exit = True

    def init_device(self):
        self.ser.write(GATEWAY_HANDSHAKE)
        return self.ser.read(1) == GATEWAY_HANDSHAKE

    def open_file(self, path):
        if self.stream_initialized:
            return 1
        try:
            self.stream = open(path, "r")
            self.stream_initialized = 1
            return 1
        except:
            return 0

    def open_serial(self):
        if self.serial_initialized:
            return 1
        if self.stream_initialized:
            return 1
        self.ser.baudrate = BAUD
        ports = self.get_safe_devices()
        for v in ports:
            self.ser.port = v.device
            self.ser.open()
            print("Testing " + str(v))
            if self.init_device():
                self.stream_initialized = True
                self.is_live = True
                print("Succesfully connected")
                self.stream = self.ser
                return 1
            print("Did not respond")
            self.ser.close()
        else:
            print("Opening serial failed")
            return 0

    def enter_sleep(self):
        self.send_message(bytes([ID_SLEEP]))

    def wake_up(self):
        self.send_message(bytes([ID_WAKE_UP]))

    def calibrate(self):
        self.send_message(bytes([ID_CALIBRATE]))

    def update_parameters(self, hpa_at_sea_level):
        msg = bytes([ID_UPDATE_PARAMETERS])
        hpa_at_sea_level = int(hpa_at_sea_level * 1000)
        msg += hpa_at_sea_level & 0xAA00
        msg += (hpa_at_sea_level & 0x00AA) >> 8
        self.send_message(msg)

    def send_message(self, msg):
        if not self.serial_initialized:
            return 0 
        #the time doesn't matter, just skip it
        start = b"$0000"
        combined_message = start + msg
        
        checksum = 0
        for char in combined_message:
            checksum ^= char
        combined_message += checksum
        self.ser.write(combined_message)

    def verify_message(self, msg):
        checksum = 0
        for i in range(len(msg) - 1):
            checksum ^= msg[i]
        return checksum == msg[-1]
    
    def parse_message(self, msg):
        self.time = bytes_to_int(msg[2:6])
        id = msg[6]
        if not id in messages:
            print("invalid ID")
            return
        decoder = messages[id]
        values = struct.unpack(decoder.format, msg[7:])
        for value in values:
            self.data[value.measurement] = value.value
            write_data_db(value, self.influx, self.time)

    def reader_from_stream(self):
        while not self.exit:
            if not self.stream_initialized:
                time.sleep(1)
                continue
            char = self.stream.read(1) 
            if  char == b"$":
                length = self.ser.read(1)
                msg = self.ser.read(length)
                combined_message = char + length + msg
                if verify_message(combined_message):
                    parse_message(combined_message)

    def get_safe_devices(self):
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

messages[ID_TELEMETRY] = Decoder("<hHHhhhhhhH", [
    "rssi",
    "altitude",
    "temperature",
    "acceleration_x",
    "acceleration_y",
    "acceleration_z",
    "gyro_x",
    "gyro_y",
    "gyro_z",
    "battery_voltage"
])

messages[ID_STATE] = Decoder("<HHH?", [
    "battery_voltage",
    "hpa_at_sea_level",
    "ground_level",
    "sleeping"
])