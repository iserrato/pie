import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import pandas as pd
import numpy as np

# read data from csv
df = pd.read_csv('plot_vars.csv', header = None).T
print(df)

# assign variable names
x,y,z = df.loc[:,0], df.loc[:,1], df.loc[:,2]

# plot results
fig = plt.figure()
ax = fig.add_subplot(projection='3d')
ax.scatter(x, y, z, c = df.loc[:,3], cmap = 'seismic')
ax.set_zlim3d(0, 100)

ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')

plt.show()
