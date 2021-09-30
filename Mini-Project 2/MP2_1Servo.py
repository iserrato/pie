import serial
import pandas as pd
import math
import numpy as np

arduinoComPort = "COM4"

baudRate = 9600

serialPort = serial.Serial(arduinoComPort, baudRate, timeout=1)

# vectors to store our data values in
x_vals = []
y_vals = []
# allows us to end the loop once we recieve an angle measurement we've already recieved
a_set = set()

while True:
  #
  # ask for a line of data from the serial port, the ".decode()" converts the
  # data from an "array of bytes", to a string
  #
  lineOfData = serialPort.readline().decode()

  # check if data was received

  if len(lineOfData) > 0:

    # data was received, convert it into 4 integers

    print("")
    angle, val = (int(x) for x in lineOfData.split(','))

    # print the results

    print("angle = " + str(angle), end="")
    print(", val = " + str(val), end="")

    # break condition
    if angle in pt_set:
        break
    a_set.add(angle)

    # calculate the distance and angle in radians from input data
    distance = -(val - 716.079)/10.4921 # a linear model
    theta = angle * math.pi/180.0

    # calculate cartesian points from polar
    cart_x = distance * math.cos(theta - 90)
    cart_y = distance * math.sin(theta - 90)

    x_vals.append(cart_x)
    y_vals.append(cart_y)


print(x_vals[:10])
print(y_vals[:10])

# save variables into csv so plotting can happen in another file
np.savetxt('simgle_scan.csv', [x_vals, y_vals], delimiter = ", ", fmt = "% s")
