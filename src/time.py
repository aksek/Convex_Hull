# Kowalski, Convex_Hull

from plotly.subplots import make_subplots
import plotly.graph_objects as go
import numpy as np
import pandas as pd

df = pd.read_csv('./data/time_data.txt')

trace1 = go.Scatter(
	
	x=df.x, y=df.y_quickhull,
    	name = 'incremental',
    	showlegend = True
	)
	
trace2 = go.Scatter(
	
	x=df.x, y = 0.126451 * df.x - 86.330999,
    	name = 'regression',
    	showlegend = True
	)
	
data = [trace1, trace2]

layout = go.Layout(
	title= dict(
		text = 'time complexity', 
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
	),
	xaxis_title="Number of points",
    	yaxis_title="Time required"
)

fig = go.Figure(data=data, layout=layout)
fig.show()
