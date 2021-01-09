import tkinter as tk
from tkinter.filedialog import askopenfilename
from matplotlib import pyplot as plt
from matplotlib import animation
from matplotlib.figure import Figure
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from time import time

REFRESH = 16

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
    
    def update(self, i): 
        relative_time = self.clock()
        self.ax.set_xlim(
            relative_time - 60, relative_time)
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
            gw.data["gyro_x"],
            gw.data["gyro_y"],
            gw.data["gyro_z"]
        ]
        super().__init__(root, gw.get_time, dataLists)
        self.ax.set_ylim(-3.14, 3.14)
        self.ax.set_title("rotation - radians/s")
        self.ax.axhline(0, color='gray')

class AccelerationGraph(GenericGraph):
    def __init__(self, root, gw):
        dataLists = [
            gw.data["acceleration_x"],
            gw.data["acceleration_y"],
            gw.data["acceleration_z"]
        ]
        super().__init__(root, gw.get_time, dataLists)
        self.ax.set_ylim(-20, 20)
        self.ax.set_title("acceleration - m/s²")
        self.ax.axhline(0, color='gray')

class AltitudeGraph(GenericGraph):
    def __init__(self, root, gw):
        super().__init__(root, gw.get_time, [gw.data["altitude"]])
        self.ax.set_ylim(0, 200)
        self.ax.set_title("altitude - m")

class Parameters(tk.Frame):
    def __init__(self, root, gw):
        super().__init__(root)
        self.value = tk.StringVar()
        self.gw = gw
        pressure_label = tk.Label(self, text = "hPa at sea-level")
        pressure_label.grid(row = 0, column = 0)
        pressure = tk.Entry(self, width = 13, textvariable = self.value)
        pressure.grid(row = 0, column = 1)
        confirm = tk.Button(self, text="update parameters", command = self.on_click)
        confirm.grid(row = 1, column = 0)

    def on_click(self):
        num = float(self.value.get())
        self.gw.update_parameters(num)