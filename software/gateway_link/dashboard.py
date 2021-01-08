import tkinter as tk
from utils.gateway import Gateway
from utils.data_handling import init_db
from utils.widgets import *

def main():
    client = init_db(True)
    gw = Gateway(client)

    root = tk.Tk()

    open_serial = tk.Button(root, text="open serial", command = gw.open_serial)
    open_file = ButtonFile(root, text="open file", command = gw.open_file)
    calibrate = tk.Button(root, text="calibrate", command = gw.calibrate)
    sleep = tk.Button(root, text="sleep", command = gw.enter_sleep)
    wake_up = tk.Button(root, text="wake up", command = gw.wake_up)
    is_sleeping = TextLastValue(root, "sleeping: ", gw.data["sleeping"])
    voltage = TextLastValue(root, "voltage: ", gw.data["battery_voltage"])
    rssi = TextLastValue(root, "rssi on rocket: ", gw.data["rssi"])

    altitude = AltitudeGraph(root, gw)

    open_serial.grid(column = 0, row = 0)
    open_file.grid(column = 0, row = 1)
    calibrate.grid(column = 0, row = 2)
    sleep.grid(column = 0, row = 3)
    wake_up.grid(column = 0, row = 4)

    is_sleeping.grid(column = 1, row = 0)
    voltage.grid(column = 1, row = 1)
    rssi.grid(column = 1, row = 2)

    altitude.widget.grid(column = 2, row = 0)

    def on_close():
        gw.stop()
        root.destroy()

    root.protocol("WM_DELETE_WINDOW", on_close)
    root.mainloop()

main()