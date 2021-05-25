################################
#GENERATED FILE DO NOT EDIT
################################

from enum import Enum
import struct

def scaledFloat_to_uint(value, scale):
    return value * scale

def uint_to_scaledFloat(value, scale):
    return value / scale

def packedFloat_to_uint(value, minValue, maxValue, size):
    intMax = (1 << size * 8) - 1
    if(value < minValue):
      return 0
    if(value > maxValue):
      return intMax
    ratio = (value - minValue) / (maxValue - minValue)
    return 1 + ((intMax - 2)) * ratio
  
def uint_to_packedFloat(value, minValue, maxValue, size):
    intMax = (1 << size * 8) - 1
    if(value <= 0):
      return minValue - 1.0
    if(value >= intMax):
      return maxValue + 1.0
    ratio = (value - 1) / (intMax - 2)
    return ratio * (maxValue - minValue) + minValue

class state(Enum):
    sleeping = 0
    awake = 1
    ready = 2
    ascending = 3
    falling = 4
    landed = 5
class nodes(Enum):
    local = 0
    rocket = 1
    ground = 2
    relay = 3
class fields(Enum):
    local_timestamp = 0
    ms_since_boot = 1
    declination = 2
    this_to_42 = 3
    is_enabled = 4
    address = 5
    altitude = 6
    temperature = 7
    acc_x = 8
    acc_y = 9
    acc_z = 10
    gyro_x = 11
    gyro_y = 12
    gyro_z = 13
    mag_x = 14
    mag_y = 15
    mag_z = 16
    voltage = 17
    state = 18
    rssi = 19
class messages(Enum):
    local_timestamp = 0
    timestamp = 1
    handshake = 2
    simple_calibration = 3
    mag_calibration = 4
    wipe_flash = 5
    play_music = 6
    set_logging = 7
    flash_address = 8
    bmp = 9
    mpu = 10
    battery_voltage = 11
    set_state = 12
    state = 13
    rssi = 14
    ms_since_boot = 15
class categories(Enum):
    none = 0
class local_timestamp_from_local_to_local:
    def __init__(self):
        self._sender = nodes.local
        self._receiver = nodes.local
        self._message = messages.local_timestamp
        self._category = categories.none
        self._id = 0
        self._size = 4
        self._local_timestamp = 0
    def get_sender(self):
        return self._sender
    def get_receiver(self):
        return self._receiver
    def get_message(self):
        return self._message
    def get_id(self):
        return self._id
    def get_size(self):
        return self._size
    def get_category(self):
        return self._category
    def set_local_timestamp(self, value):
        self._local_timestamp = value
    def build_buf(self):
        buf = b""
        buf += struct.pack("<L", self._local_timestamp)
        return buf
    def get_local_timestamp(self):
        return self._local_timestamp
    def get_all_data(self):
        data = []
        data.append((fields.local_timestamp, self.get_local_timestamp()))
        return data
    def parse_buf(self, buf):
        index = 0
        self._local_timestamp = struct.unpack_from("<L", buf, index)[0]
        index += 4
        return
class timestamp_from_rocket_to_ground:
    def __init__(self):
        self._sender = nodes.rocket
        self._receiver = nodes.ground
        self._message = messages.timestamp
        self._category = categories.none
        self._id = 1
        self._size = 4
        self._ms_since_boot = 0
    def get_sender(self):
        return self._sender
    def get_receiver(self):
        return self._receiver
    def get_message(self):
        return self._message
    def get_id(self):
        return self._id
    def get_size(self):
        return self._size
    def get_category(self):
        return self._category
    def set_ms_since_boot(self, value):
        self._ms_since_boot = value
    def build_buf(self):
        buf = b""
        buf += struct.pack("<L", self._ms_since_boot)
        return buf
    def get_ms_since_boot(self):
        return self._ms_since_boot
    def get_all_data(self):
        data = []
        data.append((fields.ms_since_boot, self.get_ms_since_boot()))
        return data
    def parse_buf(self, buf):
        index = 0
        self._ms_since_boot = struct.unpack_from("<L", buf, index)[0]
        index += 4
        return
class handshake_from_ground_to_rocket:
    def __init__(self):
        self._sender = nodes.ground
        self._receiver = nodes.rocket
        self._message = messages.handshake
        self._category = categories.none
        self._id = 2
        self._size = 0
    def get_sender(self):
        return self._sender
    def get_receiver(self):
        return self._receiver
    def get_message(self):
        return self._message
    def get_id(self):
        return self._id
    def get_size(self):
        return self._size
    def get_category(self):
        return self._category
    def build_buf(self):
        buf = b""
        return buf
    def get_all_data(self):
        data = []
        return data
    def parse_buf(self, buf):
        index = 0
        return
class handshake_from_rocket_to_ground:
    def __init__(self):
        self._sender = nodes.rocket
        self._receiver = nodes.ground
        self._message = messages.handshake
        self._category = categories.none
        self._id = 3
        self._size = 0
    def get_sender(self):
        return self._sender
    def get_receiver(self):
        return self._receiver
    def get_message(self):
        return self._message
    def get_id(self):
        return self._id
    def get_size(self):
        return self._size
    def get_category(self):
        return self._category
    def build_buf(self):
        buf = b""
        return buf
    def get_all_data(self):
        data = []
        return data
    def parse_buf(self, buf):
        index = 0
        return
class simple_calibration_from_ground_to_rocket:
    def __init__(self):
        self._sender = nodes.ground
        self._receiver = nodes.rocket
        self._message = messages.simple_calibration
        self._category = categories.none
        self._id = 4
        self._size = 0
    def get_sender(self):
        return self._sender
    def get_receiver(self):
        return self._receiver
    def get_message(self):
        return self._message
    def get_id(self):
        return self._id
    def get_size(self):
        return self._size
    def get_category(self):
        return self._category
    def build_buf(self):
        buf = b""
        return buf
    def get_all_data(self):
        data = []
        return data
    def parse_buf(self, buf):
        index = 0
        return
class mag_calibration_from_ground_to_rocket:
    def __init__(self):
        self._sender = nodes.ground
        self._receiver = nodes.rocket
        self._message = messages.mag_calibration
        self._category = categories.none
        self._id = 5
        self._size = 4
        self._declination = 0
    def get_sender(self):
        return self._sender
    def get_receiver(self):
        return self._receiver
    def get_message(self):
        return self._message
    def get_id(self):
        return self._id
    def get_size(self):
        return self._size
    def get_category(self):
        return self._category
    def set_declination(self, value):
        self._declination = value
    def build_buf(self):
        buf = b""
        buf += struct.pack("<f", self._declination)
        return buf
    def get_declination(self):
        return self._declination
    def get_all_data(self):
        data = []
        data.append((fields.declination, self.get_declination()))
        return data
    def parse_buf(self, buf):
        index = 0
        self._declination = struct.unpack_from("<f", buf, index)[0]
        index += 4
        return
class wipe_flash_from_ground_to_rocket:
    def __init__(self):
        self._sender = nodes.ground
        self._receiver = nodes.rocket
        self._message = messages.wipe_flash
        self._category = categories.none
        self._id = 6
        self._size = 1
        self._this_to_42 = 0
    def get_sender(self):
        return self._sender
    def get_receiver(self):
        return self._receiver
    def get_message(self):
        return self._message
    def get_id(self):
        return self._id
    def get_size(self):
        return self._size
    def get_category(self):
        return self._category
    def set_this_to_42(self, value):
        self._this_to_42 = value
    def build_buf(self):
        buf = b""
        buf += struct.pack("<B", self._this_to_42)
        return buf
    def get_this_to_42(self):
        return self._this_to_42
    def get_all_data(self):
        data = []
        data.append((fields.this_to_42, self.get_this_to_42()))
        return data
    def parse_buf(self, buf):
        index = 0
        self._this_to_42 = struct.unpack_from("<B", buf, index)[0]
        index += 1
        return
class play_music_from_ground_to_rocket:
    def __init__(self):
        self._sender = nodes.ground
        self._receiver = nodes.rocket
        self._message = messages.play_music
        self._category = categories.none
        self._id = 7
        self._size = 0
    def get_sender(self):
        return self._sender
    def get_receiver(self):
        return self._receiver
    def get_message(self):
        return self._message
    def get_id(self):
        return self._id
    def get_size(self):
        return self._size
    def get_category(self):
        return self._category
    def build_buf(self):
        buf = b""
        return buf
    def get_all_data(self):
        data = []
        return data
    def parse_buf(self, buf):
        index = 0
        return
class set_logging_from_ground_to_rocket:
    def __init__(self):
        self._sender = nodes.ground
        self._receiver = nodes.rocket
        self._message = messages.set_logging
        self._category = categories.none
        self._id = 8
        self._size = 1
        self._bit_field = 0
    def get_sender(self):
        return self._sender
    def get_receiver(self):
        return self._receiver
    def get_message(self):
        return self._message
    def get_id(self):
        return self._id
    def get_size(self):
        return self._size
    def get_category(self):
        return self._category
    def set_is_enabled(self, value):
        self._bit_field =  value * (self._bit_field | (1 << 0)) + (not value) * (self._bit_field & ~(1 << 0))
    def build_buf(self):
        buf = b""
        buf += struct.pack("<B", self._bit_field)
        return buf
    def get_is_enabled(self):
        return self._bit_field & (1 << 0)
    def get_all_data(self):
        data = []
        data.append((fields.is_enabled, self.get_is_enabled()))
        return data
    def parse_buf(self, buf):
        index = 0
        self._bit_field = struct.unpack_from("<B", buf, index)[0]
        index += 1
        return
class flash_address_from_rocket_to_ground:
    def __init__(self):
        self._sender = nodes.rocket
        self._receiver = nodes.ground
        self._message = messages.flash_address
        self._category = categories.none
        self._id = 9
        self._size = 4
        self._address = 0
    def get_sender(self):
        return self._sender
    def get_receiver(self):
        return self._receiver
    def get_message(self):
        return self._message
    def get_id(self):
        return self._id
    def get_size(self):
        return self._size
    def get_category(self):
        return self._category
    def set_address(self, value):
        self._address = value
    def build_buf(self):
        buf = b""
        buf += struct.pack("<L", self._address)
        return buf
    def get_address(self):
        return self._address
    def get_all_data(self):
        data = []
        data.append((fields.address, self.get_address()))
        return data
    def parse_buf(self, buf):
        index = 0
        self._address = struct.unpack_from("<L", buf, index)[0]
        index += 4
        return
class bmp_from_rocket_to_ground:
    def __init__(self):
        self._sender = nodes.rocket
        self._receiver = nodes.ground
        self._message = messages.bmp
        self._category = categories.none
        self._id = 10
        self._size = 8
        self._altitude = 0
        self._temperature = 0
    def get_sender(self):
        return self._sender
    def get_receiver(self):
        return self._receiver
    def get_message(self):
        return self._message
    def get_id(self):
        return self._id
    def get_size(self):
        return self._size
    def get_category(self):
        return self._category
    def set_altitude(self, value):
        self._altitude = value
    def set_temperature(self, value):
        self._temperature = value
    def build_buf(self):
        buf = b""
        buf += struct.pack("<f", self._altitude)
        buf += struct.pack("<f", self._temperature)
        return buf
    def get_altitude(self):
        return self._altitude
    def get_temperature(self):
        return self._temperature
    def get_all_data(self):
        data = []
        data.append((fields.altitude, self.get_altitude()))
        data.append((fields.temperature, self.get_temperature()))
        return data
    def parse_buf(self, buf):
        index = 0
        self._altitude = struct.unpack_from("<f", buf, index)[0]
        index += 4
        self._temperature = struct.unpack_from("<f", buf, index)[0]
        index += 4
        return
class mpu_from_rocket_to_ground:
    def __init__(self):
        self._sender = nodes.rocket
        self._receiver = nodes.ground
        self._message = messages.mpu
        self._category = categories.none
        self._id = 11
        self._size = 36
        self._acc_x = 0
        self._acc_y = 0
        self._acc_z = 0
        self._gyro_x = 0
        self._gyro_y = 0
        self._gyro_z = 0
        self._mag_x = 0
        self._mag_y = 0
        self._mag_z = 0
    def get_sender(self):
        return self._sender
    def get_receiver(self):
        return self._receiver
    def get_message(self):
        return self._message
    def get_id(self):
        return self._id
    def get_size(self):
        return self._size
    def get_category(self):
        return self._category
    def set_acc_x(self, value):
        self._acc_x = value
    def set_acc_y(self, value):
        self._acc_y = value
    def set_acc_z(self, value):
        self._acc_z = value
    def set_gyro_x(self, value):
        self._gyro_x = value
    def set_gyro_y(self, value):
        self._gyro_y = value
    def set_gyro_z(self, value):
        self._gyro_z = value
    def set_mag_x(self, value):
        self._mag_x = value
    def set_mag_y(self, value):
        self._mag_y = value
    def set_mag_z(self, value):
        self._mag_z = value
    def build_buf(self):
        buf = b""
        buf += struct.pack("<f", self._acc_x)
        buf += struct.pack("<f", self._acc_y)
        buf += struct.pack("<f", self._acc_z)
        buf += struct.pack("<f", self._gyro_x)
        buf += struct.pack("<f", self._gyro_y)
        buf += struct.pack("<f", self._gyro_z)
        buf += struct.pack("<f", self._mag_x)
        buf += struct.pack("<f", self._mag_y)
        buf += struct.pack("<f", self._mag_z)
        return buf
    def get_acc_x(self):
        return self._acc_x
    def get_acc_y(self):
        return self._acc_y
    def get_acc_z(self):
        return self._acc_z
    def get_gyro_x(self):
        return self._gyro_x
    def get_gyro_y(self):
        return self._gyro_y
    def get_gyro_z(self):
        return self._gyro_z
    def get_mag_x(self):
        return self._mag_x
    def get_mag_y(self):
        return self._mag_y
    def get_mag_z(self):
        return self._mag_z
    def get_all_data(self):
        data = []
        data.append((fields.acc_x, self.get_acc_x()))
        data.append((fields.acc_y, self.get_acc_y()))
        data.append((fields.acc_z, self.get_acc_z()))
        data.append((fields.gyro_x, self.get_gyro_x()))
        data.append((fields.gyro_y, self.get_gyro_y()))
        data.append((fields.gyro_z, self.get_gyro_z()))
        data.append((fields.mag_x, self.get_mag_x()))
        data.append((fields.mag_y, self.get_mag_y()))
        data.append((fields.mag_z, self.get_mag_z()))
        return data
    def parse_buf(self, buf):
        index = 0
        self._acc_x = struct.unpack_from("<f", buf, index)[0]
        index += 4
        self._acc_y = struct.unpack_from("<f", buf, index)[0]
        index += 4
        self._acc_z = struct.unpack_from("<f", buf, index)[0]
        index += 4
        self._gyro_x = struct.unpack_from("<f", buf, index)[0]
        index += 4
        self._gyro_y = struct.unpack_from("<f", buf, index)[0]
        index += 4
        self._gyro_z = struct.unpack_from("<f", buf, index)[0]
        index += 4
        self._mag_x = struct.unpack_from("<f", buf, index)[0]
        index += 4
        self._mag_y = struct.unpack_from("<f", buf, index)[0]
        index += 4
        self._mag_z = struct.unpack_from("<f", buf, index)[0]
        index += 4
        return
class battery_voltage_from_rocket_to_ground:
    def __init__(self):
        self._sender = nodes.rocket
        self._receiver = nodes.ground
        self._message = messages.battery_voltage
        self._category = categories.none
        self._id = 12
        self._size = 4
        self._voltage = 0
    def get_sender(self):
        return self._sender
    def get_receiver(self):
        return self._receiver
    def get_message(self):
        return self._message
    def get_id(self):
        return self._id
    def get_size(self):
        return self._size
    def get_category(self):
        return self._category
    def set_voltage(self, value):
        self._voltage = value
    def build_buf(self):
        buf = b""
        buf += struct.pack("<f", self._voltage)
        return buf
    def get_voltage(self):
        return self._voltage
    def get_all_data(self):
        data = []
        data.append((fields.voltage, self.get_voltage()))
        return data
    def parse_buf(self, buf):
        index = 0
        self._voltage = struct.unpack_from("<f", buf, index)[0]
        index += 4
        return
class set_state_from_ground_to_rocket:
    def __init__(self):
        self._sender = nodes.ground
        self._receiver = nodes.rocket
        self._message = messages.set_state
        self._category = categories.none
        self._id = 13
        self._size = 1
        self._state = 0
    def get_sender(self):
        return self._sender
    def get_receiver(self):
        return self._receiver
    def get_message(self):
        return self._message
    def get_id(self):
        return self._id
    def get_size(self):
        return self._size
    def get_category(self):
        return self._category
    def set_state(self, value):
        self._state = value.value
    def build_buf(self):
        buf = b""
        buf += struct.pack("<B", self._state)
        return buf
    def get_state(self):
        return state(self._state)
    def get_all_data(self):
        data = []
        data.append((fields.state, self.get_state()))
        return data
    def parse_buf(self, buf):
        index = 0
        self._state = struct.unpack_from("<B", buf, index)[0]
        index += 1
        return
class state_from_rocket_to_ground:
    def __init__(self):
        self._sender = nodes.rocket
        self._receiver = nodes.ground
        self._message = messages.state
        self._category = categories.none
        self._id = 14
        self._size = 1
        self._state = 0
    def get_sender(self):
        return self._sender
    def get_receiver(self):
        return self._receiver
    def get_message(self):
        return self._message
    def get_id(self):
        return self._id
    def get_size(self):
        return self._size
    def get_category(self):
        return self._category
    def set_state(self, value):
        self._state = value.value
    def build_buf(self):
        buf = b""
        buf += struct.pack("<B", self._state)
        return buf
    def get_state(self):
        return state(self._state)
    def get_all_data(self):
        data = []
        data.append((fields.state, self.get_state()))
        return data
    def parse_buf(self, buf):
        index = 0
        self._state = struct.unpack_from("<B", buf, index)[0]
        index += 1
        return
class rssi_from_rocket_to_ground:
    def __init__(self):
        self._sender = nodes.rocket
        self._receiver = nodes.ground
        self._message = messages.rssi
        self._category = categories.none
        self._id = 15
        self._size = 2
        self._rssi = 0
    def get_sender(self):
        return self._sender
    def get_receiver(self):
        return self._receiver
    def get_message(self):
        return self._message
    def get_id(self):
        return self._id
    def get_size(self):
        return self._size
    def get_category(self):
        return self._category
    def set_rssi(self, value):
        self._rssi = scaledFloat_to_uint(value, 100)
    def build_buf(self):
        buf = b""
        buf += struct.pack("<h", self._rssi)
        return buf
    def get_rssi(self):
        return uint_to_scaledFloat(self._rssi, 100)
    def get_all_data(self):
        data = []
        data.append((fields.rssi, self.get_rssi()))
        return data
    def parse_buf(self, buf):
        index = 0
        self._rssi = struct.unpack_from("<h", buf, index)[0]
        index += 2
        return
class rssi_from_relay_to_ground:
    def __init__(self):
        self._sender = nodes.relay
        self._receiver = nodes.ground
        self._message = messages.rssi
        self._category = categories.none
        self._id = 16
        self._size = 2
        self._rssi = 0
    def get_sender(self):
        return self._sender
    def get_receiver(self):
        return self._receiver
    def get_message(self):
        return self._message
    def get_id(self):
        return self._id
    def get_size(self):
        return self._size
    def get_category(self):
        return self._category
    def set_rssi(self, value):
        self._rssi = scaledFloat_to_uint(value, 100)
    def build_buf(self):
        buf = b""
        buf += struct.pack("<h", self._rssi)
        return buf
    def get_rssi(self):
        return uint_to_scaledFloat(self._rssi, 100)
    def get_all_data(self):
        data = []
        data.append((fields.rssi, self.get_rssi()))
        return data
    def parse_buf(self, buf):
        index = 0
        self._rssi = struct.unpack_from("<h", buf, index)[0]
        index += 2
        return
class ms_since_boot_from_rocket_to_ground:
    def __init__(self):
        self._sender = nodes.rocket
        self._receiver = nodes.ground
        self._message = messages.ms_since_boot
        self._category = categories.none
        self._id = 17
        self._size = 4
        self._ms_since_boot = 0
    def get_sender(self):
        return self._sender
    def get_receiver(self):
        return self._receiver
    def get_message(self):
        return self._message
    def get_id(self):
        return self._id
    def get_size(self):
        return self._size
    def get_category(self):
        return self._category
    def set_ms_since_boot(self, value):
        self._ms_since_boot = value
    def build_buf(self):
        buf = b""
        buf += struct.pack("<L", self._ms_since_boot)
        return buf
    def get_ms_since_boot(self):
        return self._ms_since_boot
    def get_all_data(self):
        data = []
        data.append((fields.ms_since_boot, self.get_ms_since_boot()))
        return data
    def parse_buf(self, buf):
        index = 0
        self._ms_since_boot = struct.unpack_from("<L", buf, index)[0]
        index += 4
        return
def id_to_message_class(id):
    if id == 0:
        receiver = local_timestamp_from_local_to_local()
        return receiver
    if id == 1:
        receiver = timestamp_from_rocket_to_ground()
        return receiver
    if id == 2:
        receiver = handshake_from_ground_to_rocket()
        return receiver
    if id == 3:
        receiver = handshake_from_rocket_to_ground()
        return receiver
    if id == 4:
        receiver = simple_calibration_from_ground_to_rocket()
        return receiver
    if id == 5:
        receiver = mag_calibration_from_ground_to_rocket()
        return receiver
    if id == 6:
        receiver = wipe_flash_from_ground_to_rocket()
        return receiver
    if id == 7:
        receiver = play_music_from_ground_to_rocket()
        return receiver
    if id == 8:
        receiver = set_logging_from_ground_to_rocket()
        return receiver
    if id == 9:
        receiver = flash_address_from_rocket_to_ground()
        return receiver
    if id == 10:
        receiver = bmp_from_rocket_to_ground()
        return receiver
    if id == 11:
        receiver = mpu_from_rocket_to_ground()
        return receiver
    if id == 12:
        receiver = battery_voltage_from_rocket_to_ground()
        return receiver
    if id == 13:
        receiver = set_state_from_ground_to_rocket()
        return receiver
    if id == 14:
        receiver = state_from_rocket_to_ground()
        return receiver
    if id == 15:
        receiver = rssi_from_rocket_to_ground()
        return receiver
    if id == 16:
        receiver = rssi_from_relay_to_ground()
        return receiver
    if id == 17:
        receiver = ms_since_boot_from_rocket_to_ground()
        return receiver
