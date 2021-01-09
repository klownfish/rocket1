import tkinter as tk
from utils.gateway import Gateway
from utils.data_handling import init_db
from utils.widgets import *

def main():
    client = init_db(True)
    gw = Gateway(client)

    root = tk.Tk()
    padding = {"padx": 5, "pady": 5}
    settings = tk.Frame(root)

    open_serial = tk.Button(settings, text="open serial", command = gw.open_serial, **padding)
    open_file = ButtonFile(settings, text="open file", command = gw.open_file, **padding)
    calibrate = tk.Button(settings, text="calibrate", command = gw.calibrate, **padding)
    sleep = tk.Button(settings, text="sleep", command = gw.enter_sleep, **padding)
    wake_up = tk.Button(settings, text="wake up", command = gw.wake_up, **padding)
    is_sleeping = TextLastValue(settings, "sleeping: ", gw.data["sleeping"])
    voltage = TextLastValue(settings, "voltage: ", gw.data["battery_voltage"])
    rssi = TextLastValue(settings, "rssi on rocket: ", gw.data["rssi"])
    ground_level = TextLastValue(settings, "ground level: ", gw.data["ground_level"])
    pressure = TextLastValue(settings, "hPa at sea level: ", gw.data["hpa_at_sea_level"])
    parameters = Parameters(settings, gw)
    
    altitude = AltitudeGraph(root, gw)
    gyro = GyroGraph(root, gw)
    acceleration = AccelerationGraph(root, gw)
    open_serial.grid(column = 0, row = 0)
    open_file.grid(column = 0, row = 1)
    calibrate.grid(column = 0, row = 2)
    sleep.grid(column = 0, row = 3)
    wake_up.grid(column = 0, row = 4)
    parameters.grid(column = 0, row = 5)

    is_sleeping.grid(column = 1, row = 0)
    voltage.grid(column = 1, row = 1)
    rssi.grid(column = 1, row = 2)
    ground_level.grid(column = 1, row = 3)
    pressure.grid(column = 1, row = 4)

    altitude.widget.grid(column = 0, row = 0, **padding)
    gyro.widget.grid(column = 0, row = 1, **padding)
    acceleration.widget.grid(column = 1, row = 0, **padding)

    settings.grid(column = 1,row = 1)
    def on_close():
        gw.stop()
        root.destroy()

    root.protocol("WM_DELETE_WINDOW", on_close)
    root.mainloop()

main()