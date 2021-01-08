import influxdb
import datetime

class Timeseries():
    def __init__(self):
        self.x = []
        self.y = []

class Data():
    def __init__(measurement, value):
        self.measurement = measurement
        self.value = value

def init_db(reset = False):
    try:
        client = InfluxDBClient(host='localhost', port='8086')
        client.switch_database(INFLUX_NAME)
        if reset:
            reset_db(client)
        return client
    except:
        print("COULD NOT CONNECT TO INFLUX. NO DATA WILL BE WRITTEN TO THE SERVER")
        return 0

def reset_db(client):
    client.drop_database(INFLUX_NAME)
    client.create_database(INFLUX_NAME)

def write_data_db(value, client, time = False):
    points = []
    for v in data:
        point = {
            "measurement": "rocket",
            "fields": {
                v.measurement: v.value,
            }
        }
        if time:
            point["time"] = time
        points.append(point)
    try:
        client.write_points(points)
    except:
        print("could not write to the influx server")
    return 0