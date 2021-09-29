import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import pandas as pd
import numpy as np


#[x_vals, y_vals, z_vals, d_array, phi_array, theta_array]
df = pd.read_csv('plot_vars.csv', header = None).T
print(df)

x,y,z = df.loc[:,0], df.loc[:,1], df.loc[:,2]

# r = df.loc[:,3]
# p = df.loc[:,4]
#
# R, P = np.meshgrid(r, p)
# Z = ((R**2 - 1)**2)
#
# X, Y = R*np.cos(P), R*np.sin(P)
#
# fig = plt.figure()
# ax = fig.add_subplot(projection='3d')
# ax.scatter(X, Y, Z)

fig = plt.figure()
ax = fig.add_subplot(projection='3d')
ax.scatter(x, y, z, c = df.loc[:,3], cmap = 'seismic')
ax.set_zlim3d(0, 100)

ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')

plt.show()

max()
