# Initital communication between Arduino and Python

import serial
import serial.tools.list_ports as list_ports
import time
import matplotlib.pyplot as plt
import csv


left_motor = []
right_motor = []
left_sensor = []
right_sensor = []

class Serial_cmd:
    Arduino_IDs = ((0x2341, 0x0043), (0x2341, 0x0001), 
                   (0x2A03, 0x0043), (0x2341, 0x0243), 
                   (0x0403, 0x6001), (0x1A86, 0x7523))
    
    def __init__(self, port=''):
        if port == '':
            self.dev = None
            self.connected = False
            devices = list_ports.comports()
            for device in devices:
                if (device.vid, device.pid) in Serial_cmd.Arduino_IDs:
                    try:
                        self.dev = serial.Serial(device.device, 115200)
                        self.connected = True
                        print('Connected to {!s}...'.format(device.device))
                    except:
                        pass
                if self.connected:
                    break
        else:
            try:
                self.dev = serial.Serial(port, 115200)
                self.connected = True
            except:
                self.edev = None
                self.connected = False
    
    def read_data(self):
        if self.connected:
            left_sensor_val = self.dev.readline().decode().rstrip()
            right_sensor_val = self.dev.readline().decode().rstrip()
            left_motor_val = self.dev.readline().decode().rstrip()
            right_motor_val = self.dev.readline().decode().rstrip()
            if left_motor_val == '' or left_sensor_val == '' or right_sensor_val == '' or right_motor_val == '':
                return []
            return (float(left_sensor_val), float(right_sensor_val), float(left_motor_val), float(right_motor_val))

def format_data(data):
    if len(data) > 0:
        left_sensor.append(data[0])
        right_sensor.append(data[1])
        left_motor.append(data[2])
        right_motor.append(data[3])

Obj = Serial_cmd()
values = []
time.sleep(2)
t_len = 800
for i in range(t_len): 
    data = Obj.read_data()
    print(data)
    format_data(data)

t = [i for i in range(len(left_sensor))]
plt.plot(t, left_sensor)
plt.plot(t, left_motor)
plt.plot(t, right_motor)
plt.plot(t, right_sensor)



with open('data_out.csv', 'w', newline='') as csvfile:
    writer = csv.writer(csvfile, delimiter=' ', quotechar='|', quoting=csv.QUOTE_MINIMAL)
    writer.writerow(left_sensor)
    writer.writerow(right_sensor)
    writer.writerow(left_motor)
    writer.writerow(right_motor)

plt.show()