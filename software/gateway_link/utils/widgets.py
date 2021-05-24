import tkinter as tk
from tkinter.filedialog import askopenfilename
from matplotlib import pyplot as plt
from matplotlib import animation
from matplotlib.figure import Figure
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from time import time

REFRESH = 16

VIEWRANGE = 30
##################
#Class to display TimeSeries
##################
#
#__init__(root, database, datalists)
#root - TKinter root window
#clock - the clock that will be used
#time_serise - a list with TimeSeries to display
class GenericGraph():
    def __init__(self, root, clock, time_series, width = 9, height = 5):
        self.clock = clock
        self.time_series = time_series
        self.fig = plt.Figure(figsize=(width, height), dpi=100)
        self.ax = self.fig.add_subplot(111)    
        self.lines = []
        #create a line for every series
        for _ in time_series:
            line, = self.ax.plot([], [])
            self.lines.append(line)
        
        self.canvas = FigureCanvasTkAgg(self.fig, master=root)
        self.widget = self.canvas.get_tk_widget()
        self.ani = animation.FuncAnimation(
            self.fig, self.update, interval=REFRESH)
    
    def update(self, _): 
        relative_time = self.clock()
        self.ax.set_xlim(
            relative_time - VIEWRANGE, relative_time)
        for i in range(len(self.time_series)):
            self.lines[i].set_data(self.time_series[i].x, self.time_series[i].y)

        return self.lines,

###################
#class to display the latest value from a TimeSeries
###################
#
#__init__(self, root, text, value)
#root - tkinter root
#text - displayed before the value
#value - the TimeSeries that the value will be taken from
class TextLastValue(tk.Label):
    def __init__(self, root, text, value, **kwargs):
        self.text = text
        self.stringVar = tk.StringVar()
        self.stringVar.set(text)
        self.widget = tk.Label(root, textvariable = self.stringVar)
        self.value = value
        self.root = root
        self.update()
        super().__init__(root, textvariable = self.stringVar)

    def update(self):
        self.root.after(REFRESH, self.update)    
        if len(self.value.y) == 0:
            return
        self.stringVar.set(self.text + str(self.value.y[-1]))

class EnumLastValue(tk.Label):
    def __init__(self, root, text, value, **kwargs):
        self.text = text
        self.stringVar = tk.StringVar()
        self.stringVar.set(text)
        self.widget = tk.Label(root, textvariable = self.stringVar)
        self.value = value
        self.root = root
        self.update()
        super().__init__(root, textvariable = self.stringVar)

    def update(self):
        self.root.after(REFRESH, self.update)    
        if len(self.value.y) == 0:
            return
        self.stringVar.set(self.text + self.value.y[-1].name)

    
class ButtonFile(tk.Button):
    def __init__(self, root, **kwargs):
        self.on_click = kwargs["command"]
        kwargs["command"] = self.on_click2
        super().__init__(root, **kwargs)

    def on_click2(self):
        path = askopenfilename()
        self.on_click(path)

#specific widgets
class GyroGraph(GenericGraph):
    def __init__(self, root, gw):
        dataLists = [
            gw.data["rocket"]["mpu"]["gyro_x"],
            gw.data["rocket"]["mpu"]["gyro_y"],
            gw.data["rocket"]["mpu"]["gyro_z"]
        ]
        super().__init__(root, gw.get_current_time, dataLists)
        self.ax.set_ylim(-360, 360)
        self.ax.set_title("rotation - radians/s")
        self.ax.axhline(0, color='gray')

class AccelerationGraph(GenericGraph):
    def __init__(self, root, gw):
        dataLists = [
            gw.data["rocket"]["mpu"]["acc_x"],
            gw.data["rocket"]["mpu"]["acc_y"],
            gw.data["rocket"]["mpu"]["acc_z"],
        ]
        super().__init__(root, gw.get_current_time, dataLists)
        self.ax.set_ylim(-20, 20)
        self.ax.set_title("acceleration - m/s²")
        self.ax.axhline(0, color='gray')

class AltitudeGraph(GenericGraph):
    def __init__(self, root, gw):
        super().__init__(root, gw.get_current_time, [gw.data["rocket"]["bmp"]["altitude"]])
        self.ax.set_ylim(-5, 50)
        self.ax.set_title("altitude - m")

class MagCalibration(tk.Frame):
    def __init__(self, root, gw, **settings):
        super().__init__(root)
        self.gw = gw
        self.button = tk.Button(self, text="mag calibration", command = self.update, **settings)
        self.text = tk.Text(self, height = 1, width = 5, **settings)
        tk.Label(self, text="Mag declination:").grid(column=0, row=0)
        self.text.grid(column = 0, row = 1)
        self.button.grid(column = 0, row = 2)

    def update(self):
        num = float(self.text.get("1.0", "end"))
        self.gw.calibrate_mag(num)
