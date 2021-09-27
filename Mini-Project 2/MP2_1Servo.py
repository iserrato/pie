import serial
import plotly.graph_objects as go
import pandas as pd
import math

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
    angle, val = (int(x) for x in lineOfData.split(','))

    #
    # print the results
    #

    print("angle = " + str(angle), end="")
    print(", val = " + str(val), end="")

    distance = -(val - 716.079)/10.4921
    theta = angle * math.pi/180.0

    cart_x = distance * math.cos(theta - 90)
    cart_y = distance * math.sin(theta - 90)

    x_vals.append(cart_x)
    y_vals.append(cart_y)

    if len(x_vals) > 180:
        break

print(x_vals[:10])
print(y_vals[:10])
fig = go.Figure()
fig.add_trace(go.Scatter(x=x_vals, y=y_vals))
fig.show()
