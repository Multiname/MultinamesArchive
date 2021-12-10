import pandas as pd, matplotlib.pyplot as plt, numpy as np
from mpl_toolkits.mplot3d import axes3d, Axes3D

df = pd.read_csv('data.csv')
symbols = df['Product'].str.len()
df['Symbols'] = symbols
print(df)

minCostAge = df.groupby(['BuyerID', 'Age']).sum()['Cost'].idxmin()[1]
print('\nВозраст покупательницы, купившей меньше всего товаров:', minCostAge)

largest = df[['BuyerID', 'Cost']].groupby(['BuyerID']).sum().nlargest(5, 'Cost')
smallest = df[['BuyerID', 'Cost']].groupby(['BuyerID']).sum().nsmallest(5, 'Cost')
print('\nСамые большие расходы')
print(largest)
print('\nСамые маленькие расходы')
print(smallest)

df[['Age', 'Cost']].groupby(['Age']).mean().plot.bar()
plt.show()

plt.rc('font', size=15)
fig = plt.figure()
ax = Axes3D(fig, auto_add_to_figure=False)
fig.add_axes(ax)

o = (1, 2, 3)
l, w, h = 1, 2, 3
X = np.array([[o[0], o[0] + l, o[0] + l, o[0], o[0]],
[o[0], o[0] + l, o[0] + l, o[0], o[0]],
[o[0], o[0] + l, o[0] + l, o[0], o[0]],
[o[0], o[0] + l, o[0] + l, o[0], o[0]]])
Y = np.array([[o[1], o[1], o[1] + w, o[1] + w, o[1]],
[o[1], o[1], o[1] + w, o[1] + w, o[1]],
[o[1], o[1], o[1], o[1], o[1]],
[o[1] + w, o[1] + w, o[1] + w, o[1] + w, o[1] + w]])
Z = np.array([[o[2], o[2], o[2], o[2], o[2]],
[o[2] + h, o[2] + h, o[2] + h, o[2] + h, o[2] + h],
[o[2], o[2], o[2] + h, o[2] + h, o[2]],
[o[2], o[2], o[2] + h, o[2] + h, o[2]]])

ax.plot_surface(X, Y, Z, rstride=1, cstride=1)

plt.show()
