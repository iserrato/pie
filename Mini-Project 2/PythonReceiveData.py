#      ******************************************************************
#      *                                                                *
#      *                                                                *
#      *    Example Python program that receives data from an Arduino   *
#      *                                                                *
#      *                                                                *
#      ******************************************************************


import serial
import plotly.graph_objects as go
import pandas as pd
import math
import csv
import numpy as np

#
# Note 1: This python script was designed to run with Python 3.
#
# Note 2: The script uses "pyserial" which must be installed.  If you have
#         previously installed the "serial" package, it must be uninstalled
#         first.
#
# Note 3: While this script is running you can not re-program the Arduino.
#         Before downloading a new Arduino sketch, you must exit this
#         script first.
#


#
# Set the name of the serial port.  Determine the name as follows:
#	1) From Arduino's "Tools" menu, select "Port"
#	2) It will show you which Port is used to connect to the Arduino
#
# For Windows computers, the name is formatted like: "COM6"
# For Apple computers, the name is formatted like: "/dev/tty.usbmodemfa141"
#
arduinoComPort = "COM4"


#
# Set the baud rate
# NOTE1: The baudRate for the sending and receiving programs must be the same!
# NOTE2: For faster communication, set the baudRate to 115200 below
#        and check that the arduino sketch you are using is updated as well.
#
baudRate = 9600


#
# open the serial port
#
serialPort = serial.Serial(arduinoComPort, baudRate, timeout=1)

x_vals = []
y_vals = []
z_vals = []
d_array = []
phi_array = []
theta_array = []
pt_set = set()
#
# main loop to read data from the Arduino, then display it
#
while True:
  #
  # ask for a line of data from the serial port, the ".decode()" converts the
  # data from an "array of bytes", to a string
  #
  lineOfData = serialPort.readline().decode()

  #
  # check if data was received
  #
  if len(lineOfData) > 0:

    #
    # data was received, convert it into 4 integers
    #
    print("")
    theta, phi, val = (int(x) for x in lineOfData.split(','))

    #
    # print the results
    #

    print("phi = " + str(phi), end="")
    print("theta = " + str(theta), end="")
    print(", val = " + str(val), end="")


    if (phi, theta) in pt_set:
        break
    pt_set.add((phi, theta))

    # distance = -(math.log(val/843.2))/.02313 #an exponential model
    distance = -((100000*math.log((5*val)/(4216)))/(2313)) #alternate exponential model
    theta_rad = theta * math.pi/180.0
    phi_rad = phi * math.pi/180.0

    cart_x = distance * math.sin(phi_rad) * math.cos(theta_rad)
    cart_y = distance * math.sin(theta_rad) * math.sin(phi_rad)
    cart_z = distance * math.cos(phi_rad)

    x_vals.append(cart_x)
    y_vals.append(cart_y)
    z_vals.append(cart_z)
    d_array.append(distance)
    phi_array.append(phi_rad)
    theta_array.append(theta_rad)

for i in range(10):
    print("[" , x_vals[i] , "," , y_vals[i] , "," , z_vals[i] , "]")

np.savetxt('plot_vars.csv', [x_vals, y_vals, z_vals, d_array, phi_array, theta_array], delimiter = ", ", fmt = "% s")
# fig = go.Figure(data=go.Contour(z=z_vals, x=x_vals, y=y_vals))
# fig.show()
