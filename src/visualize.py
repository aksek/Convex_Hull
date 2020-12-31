from plotly.subplots import make_subplots
import plotly.graph_objects as go
import numpy as np

pts1 = np.loadtxt(np.DataSource().open('../data/input.txt'))
x1, y1, z1 = pts1.T

pts2 = np.loadtxt(np.DataSource().open('../data/output.txt'))
x2, y2, z2 = pts2.T

fig = make_subplots(rows=2, cols=2, specs=[[{'type': 'scene'} ,{'type': 'scene'}], [{'type': 'scene'} ,{'type': 'scene'}]], subplot_titles=('input','output'))

fig.add_traces(
    [go.Scatter3d(x=x1, y=y1, z=z1, mode='markers', name = 'input points'),
     go.Mesh3d(x=x1, y=y1, z=z1, alphahull=0, opacity=0.8, colorscale=[[0, 'gold'], [0.5, 'mediumturquoise'], [1, 'magenta']], intensity = np.linspace(0, 1, 8, endpoint=True), intensitymode='cell', showscale=False, hoverinfo= 'skip'),
     go.Scatter3d(x=x2, y=y2, z=z2, mode='markers', name = 'output vertices'),
     go.Mesh3d(x=x2, y=y2, z=z2, alphahull=0, opacity=0.8, colorscale=[[0, 'gold'], [0.5, 'mediumturquoise'], [1, 'magenta']], intensity = np.linspace(0, 1, 8, endpoint=True), intensitymode='cell', showscale=False, hoverinfo= 'skip'),
     go.Mesh3d(x=x1, y=y1, z=z1, alphahull=0, opacity=1, colorscale=[[0, 'gold'], [0.5, 'mediumturquoise'], [1, 'magenta']], intensity = np.linspace(0, 1, 8, endpoint=True), intensitymode='cell', showscale=False, hoverinfo= 'skip'),
     go.Mesh3d(x=x2, y=y2, z=z2, alphahull=0, opacity=1, colorscale=[[0, 'gold'], [0.5, 'mediumturquoise'], [1, 'magenta']], intensity = np.linspace(0, 1, 8, endpoint=True), intensitymode='cell', showscale=False, hoverinfo= 'skip')],
    rows=[1, 1, 1, 1, 2, 2],
    cols=[1, 1, 2, 2, 1, 2])

fig.update_scenes(xaxis_showspikes=False,
                  yaxis_showspikes=False,
                  zaxis_showspikes=False)
                             
fig.show()
