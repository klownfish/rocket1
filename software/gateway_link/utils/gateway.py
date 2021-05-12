from collections import defaultdict
from utils.data_handling import Timeseries, write_data_db
from utils.definitions import *
from utils.decoding import Decoder
from threading import Thread
from utils.decoding import bytes_to_int, int_to_bytes
import struct
import serial
import time
import serial.tools.list_ports

messages = {}

class Gateway():
    def __init__(self, influx = False):
        self.data = defaultdict(Timeseries)
        self.influx = influx
        self.time = 0
        self.time_updated = time.time()
        self.ser = serial.Serial(timeout = 0.2) 
        self.stream = None

        self.stream_initialized = False
        self.serial_initialized = False
        self.exit = False
        self.pause = False

        self.decoders = messages
        t = Thread(target=self.reader_from_stream)
        t.start()

    def pause_thread(self):
        self.stop = True

    def resume_thread(self):
        self.stop = False

    def get_time(self):
        return self.time + time.time() - self.time_updated

    def stop(self):
        self.exit = True

    def init_device(self):
        self.pause
        self.send_message(bytes([HANDSHAKE]), True)
        time.sleep(0.5)
        init = bytes([HANDSHAKE]) in self.ser.read_all() 
        return init

    def open_file(self, path):
        if self.stream_initialized:
            return 1
        try:
            self.stream = open(path, "rb")
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
                self.serial_initialized = True
                self.is_live = True
                print("Succesfully connected")
                self.stream = self.ser
                return 1
            print("Did not respond")
            self.ser.close()
        else:
            print("Opening serial failed")
            return 0

    def start_transmission(self):
        self.send_message(bytes([GATEWAY_TRANSMIT]))

    def enter_sleep(self):
        self.send_message(bytes([ID_SLEEP]))

    def wake_up(self):
        self.send_message(bytes([ID_WAKE_UP]))

    def calibrate(self):
        self.send_message(bytes([ID_CALIBRATE]))

    def update_parameters(self, hpa_at_sea_level):
        msg = bytes([ID_UPDATE_PARAMETERS])
        hpa_at_sea_level = int(hpa_at_sea_level * 1000)
        msg += int_to_bytes(hpa_at_sea_level, 4)
        self.send_message(msg)

    def send_message(self, msg, bypass = False):
        if not (self.serial_initialized or bypass):
            return 0 
        #the time doesn't matter, just skip it
        start = b"$" + bytes([len(msg) + 6]) + b"0000"
        combined_message = start + msg
        checksum = 0
        for char in combined_message:
            checksum ^= char
        combined_message += bytes([checksum])
        self.ser.write(combined_message)

    def verify_message(self, msg):
        checksum = 0
        for i in range(len(msg) - 1):
            checksum ^= msg[i]
        return checksum == msg[-1]
    
    def parse_message(self, msg):
        new_time = bytes_to_int(msg[2:6]) / 1000
        if new_time:
            self.time = new_time
            self.time_updated = time.time()

        id = msg[6]
        if not id in messages:
            print("invalid ID")
            return

        decoder = messages[id]
        try:
            values = struct.unpack(decoder.format, msg[7:-1])
            
            for i, value in enumerate(values):
                self.data[decoder.names[i]].y.append(value / decoder.scales[i])
                self.data[decoder.names[i]].x.append(self.time)
                write_data_db(decoder.names[i], value, self.influx, self.time)
        except:
            print("bad message that passed the checksum")

    def reader_from_stream(self):
        while not self.exit:
            if not self.stream_initialized or self.pause:
                time.sleep(1)
                continue
            char = self.stream.read(1) 
            if  char != b"$":
                if char != b"":
                    print(char)
                continue
            
            length = self.stream.read(1)
            msg = self.stream.read(length[0] - 1)
            combined_message = char + length + msg

            if self.verify_message(combined_message):
                self.parse_message(combined_message)
            else:
                print("bad message")


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

messages[ID_TELEMETRY] = Decoder("<lllllllll", [
    "altitude",
    "temperature",
    "acceleration_x",
    "acceleration_y",
    "acceleration_z",
    "gyro_x",
    "gyro_y",
    "gyro_z",
    "battery_voltage"
], [
    1000,
    1000,
    1000,
    1000,
    1000,
    1000,
    1000,
    1000,
    1000
])

messages[ID_STATE] = Decoder("<llll?", [
    "rssi_rocket",
    "battery_voltage",
    "hpa_at_sea_level",
    "ground_level",
    "sleeping"
], [
    1,
    1000,
    1000,
    1000,
    1
])

messages[GATEWAY_RSSI] = Decoder("<l", ["rssi_gateway"], [1])