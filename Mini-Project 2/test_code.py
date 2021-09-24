import plotly.graph_objects as go
import pandas as pd

import numpy as np

z_data = pd.read_csv('https://raw.githubusercontent.com/plotly/datasets/master/api_docs/mt_bruno_elevation.csv')
z = z_data.values
sh_0, sh_1 = z.shape
x, y = np.linspace(0, 1, sh_0), np.linspace(0, 1, sh_1)

fig = go.Figure(data=go.Contour(z=z[0::5], x=x[0::5], y=y[0::5]))
fig.show()
