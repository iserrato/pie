import serial
import pandas as pd
import math
import csv
import numpy as np

arduinoComPort = "COM4"

baudRate = 9600

serialPort = serial.Serial(arduinoComPort, baudRate, timeout=1)

# define arrays to store data
x_vals = []
y_vals = []
z_vals = []
d_array = []
phi_array = []
theta_array = []
pt_set = set()

while True:
  lineOfData = serialPort.readline().decode()

  # check if data was received
  if len(lineOfData) > 0:

    # data was received, convert it into 4 integers

    print("")
    theta, phi, val = (int(x) for x in lineOfData.split(','))

    # print the results

    print("phi = " + str(phi), end="")
    print("theta = " + str(theta), end="")
    print(", val = " + str(val), end="")

    # break condition. If we have already recieved a specific phi, theta value, loop ends
    if (phi, theta) in pt_set:
        break
    pt_set.add((phi, theta))

    # calculate distance, theta, and phi
    distance = -((100000*math.log((5*val)/(4216)))/(2313)) #an exponential model
    theta_rad = theta * math.pi/180.0
    phi_rad = phi * math.pi/180.0

    # calculate cartesian coordinates
    cart_x = distance * math.sin(phi_rad) * math.cos(theta_rad)
    cart_y = distance * math.sin(theta_rad) * math.sin(phi_rad)
    cart_z = distance * math.cos(phi_rad)

    # add data to lists
    x_vals.append(cart_x)
    y_vals.append(cart_y)
    z_vals.append(cart_z)
    d_array.append(distance)
    phi_array.append(phi_rad)
    theta_array.append(theta_rad)

# visualize data
for i in range(10):
    print("[" , x_vals[i] , "," , y_vals[i] , "," , z_vals[i] , "]")

# save variables into csv so plotting can happen in another file
np.savetxt('plot_vars.csv', [x_vals, y_vals, z_vals, d_array, phi_array, theta_array], delimiter = ", ", fmt = "% s")
