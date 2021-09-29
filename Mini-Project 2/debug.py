import serial
import pandas as pd
import math
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D


df = pd.read_csv('simgle_scan.csv', header = None).T
print(df)

x,y = df.loc[:,0], df.loc[:,1]

fig = plt.figure()
ax = fig.add_subplot()
ax.scatter(x, y)
ax.set_xlabel('X')
ax.set_ylabel('Y')

plt.show()
