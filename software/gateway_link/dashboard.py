import tkinter as tk
from utils.gateway import Gateway
from utils.data_handling import init_db
from utils.widgets import *

def main():
    client = init_db(True)
    gw = Gateway(influx = client)

    root = tk.Tk()
    padding = {"padx": 5, "pady": 5}
    settings = tk.Frame(root)

    open_serial = tk.Button(settings, text="open serial", command = gw.open_serial, **padding)
    open_flash = ButtonFile(settings, text="open flash file", command = gw.open_flash_file, **padding)
    open_file = ButtonFile(settings, text="open radio file", command = gw.open_backup_file, **padding)
    
    calibrate = tk.Button(settings, text="simple calibration", command = gw.calibrate_simple, **padding)
    mag_calibrate = MagCalibration(settings, gw, **padding)
    sleep = tk.Button(settings, text="sleep", command = gw.enter_sleep, **padding)
    wake_up = tk.Button(settings, text="wake up", command = gw.wake_up, **padding)
    get_ready = tk.Button(settings, text="get ready!", command = gw.get_ready, **padding)
    state = EnumLastValue(settings, "state: ", gw.data["rocket"]["state"]["state"])
    voltage = TextLastValue(settings, "voltage: ", gw.data["rocket"]["battery_voltage"]["voltage"])
    rssi = TextLastValue(settings, "rssi rocket: ", gw.data["rocket"]["rssi"]["rssi"])
    rssi_gw = TextLastValue(settings, "rssi gateway: ", gw.data["relay"]["rssi"]["rssi"])
    temperature = TextLastValue(settings, "temperature: ", gw.data["rocket"]["bmp"]["temperature"])
    wipe_flash = tk.Button(settings, text = "wipe flash", command= gw.wipe_flash, **padding)
    flash_index = FlashUsed(settings, gw, **padding)
    enable_logging = tk.Button(settings, text = "enable logging", command= gw.enable_logging, **padding)
    disable_logging = tk.Button(settings, text = "disable logging", command= gw.disable_logging, **padding)

    altitude = AltitudeGraph(root, gw)
    gyro = GyroGraph(root, gw)
    acceleration = AccelerationGraph(root, gw)
    open_serial.grid(column = 0, row = 0)
    open_file.grid(column = 0, row = 1)
    open_flash.grid(column = 0, row = 2)
    calibrate.grid(column = 0, row = 3)
    mag_calibrate.grid(column = 0, row = 4)
    sleep.grid(column = 0, row = 5)
    wake_up.grid(column = 0, row = 6)
    get_ready.grid(column = 0, row = 7)
    wipe_flash.grid(column = 0, row = 8)
    enable_logging.grid(column = 0, row = 9)
    disable_logging.grid(column = 0, row = 10)
    

    state.grid(column = 1, row = 0)
    voltage.grid(column = 1, row = 1)
    rssi.grid(column = 1, row = 2)
    rssi_gw.grid(column = 1, row = 3)
    temperature.grid(column = 1, row = 4)
    flash_index.grid(column = 1, row = 5)

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