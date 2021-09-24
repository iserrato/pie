import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

df = pd.read_csv('plot_vars.csv', header = None).T
print(df)

fig = plt.figure()
ax = fig.add_subplot(projection='3d')
ax.scatter(df.loc[:,0], df.loc[:,1], df.loc[:,2])

ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')

plt.show()
