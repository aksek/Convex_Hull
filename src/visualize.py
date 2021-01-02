from plotly.subplots import make_subplots
import plotly.graph_objects as go
import numpy as np
import pandas as pd

df = pd.read_csv('./data/output.txt')

trace1 = go.Scatter3d(
	
	x=df.x, y=df.y, z=df.z, 
    	mode='markers',
    	name = 'input points'
	)
	
trace2 = go.Mesh3d(

	x=df.x, y=df.y, z=df.z,
	i=df.i, j=df.j, k=df.k,
     	opacity=1,
     	colorscale='jet',
     	intensity = df.z,
     	intensitymode='cell',
     	showscale=False,
     	hoverinfo= 'skip',
     	showlegend = True,
		name = 'convex hull'
	)
	
data = [trace1, trace2]

layout = go.Layout(
	title= dict(
		text = 'convex hull', 
		x = 0.5
	),
	titlefont=dict(
		family='Courier New, monospace',
		size=15,
		color='#7f7f7f'
	),
	paper_bgcolor='rgba(0,0,0,0)',
	plot_bgcolor='rgba(0,0,0,0)',
	scene = dict(
		xaxis_showspikes=False,
		yaxis_showspikes=False,
		zaxis_showspikes=False
	)
)

fig = go.Figure(data=data, layout=layout)
fig.show()
