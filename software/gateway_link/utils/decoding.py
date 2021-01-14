import struct
from utils.data_handling import Data

class Decoder():
    def __init__(self, pack_string, names, scales):
        self.format = pack_string
        self.names = names
        self.scales = scales
    def decode(self, msg):
        values = struct.unpack(self.format, msg)
        out = []
        for i, v in enumerate(values):
            data = Data(names[i], v)
            out.append(data)
        return out

def bytes_to_int(bytes):
    total = 0
    count = 0
    for v in bytes:
        total += v << (count * 8)
        count += 1
    return total

def int_to_bytes(num, len):
    msg = bytes()
    for i in range(len):
        msg += bytes([num &0xFF])
        num >>=8
    return msg