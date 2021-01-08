import struct
from utils.data_handling import Data

class Decoder():
    def __init__(self, pack_string, names):
        self.format = pack_string
        self.names = []

    def decode(self, msg):
        values = struct.unpack(self.format, msg)
        out = []
        for i, v in enumerate(values):
            data = Data(names[i], v)
            out.append(data)
        return out

def bytes_to_int(self, bytes):
    total = 0
    count = 0
    for v in bytes:
        total += v << (count * 8)
        count += 1
    return total
