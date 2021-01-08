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
    def __init__(self, root, clock, time_series, width = 6, height = 4):
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
    def __init__(self, root, text, value):
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
        self.ax.set_ylim(0, 255)
        self.ax.set_title("rotation - degrees")


class AccelerationGraph(GenericGraph):
    def __init__(self, root, gw):
        dataLists = [
            gw.data["acceleration_x"],
            gw.data["acceleration_y"],
            gw.data["acceleration_z"]
        ]
        super().__init__(root, gw.get_time, dataLists)
        self.ax.set_ylim(0, 20)
        self.ax.set_title("acceleration - m/s²")

class AltitudeGraph(GenericGraph):
    def __init__(self, root, gw):
        super().__init__(root, gw.get_time, [gw.data["altitude"]])
        self.ax.set_ylim(0, 200)
        self.ax.set_title("altitude - m")