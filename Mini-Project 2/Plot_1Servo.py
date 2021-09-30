import serial
import pandas as pd
import math
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# read x,y data from csv
df = pd.read_csv('simgle_scan.csv', header = None).T
#v isualize data
print(df)

# assign variable names
x,y = df.loc[:,0], df.loc[:,1]

# plot results
fig = plt.figure()
ax = fig.add_subplot()
ax.scatter(x, y)
ax.set_xlabel('X')
ax.set_ylabel('Y')

plt.show()
