import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

frame = pd.read_csv("data.csv")
frame = frame[["User_ID", "Product_ID", "Gender", "Age", "Purchase"]]
frame["ID_symbols"] = frame["Product_ID"].str.len()
print(frame.head())

grouped = frame[frame.Gender == "M"][["User_ID", "Purchase"]].groupby(["User_ID"], as_index=False).sum()
id = grouped[grouped.Purchase == grouped.Purchase.max()].iloc[0]["User_ID"]
print("ID:", id)
print("Age:", frame[frame.User_ID == id].iloc[0]["Age"])

grouped = frame[["Age", "Purchase"]].groupby(["Age"], as_index=False).mean()
grouped.plot(x="Age", y="Purchase")
plt.savefig("age_purchase.pdf")

grouped = frame[["User_ID", "Purchase"]].groupby(["User_ID"], as_index=False).sum()
print(grouped.nlargest(5, "Purchase"))
print(grouped.nsmallest(5, "Purchase"))

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

def data_for_cylinder_along_z(center_x,center_y,radius,height_z):
    z = np.linspace(0, height_z, 50)
    theta = np.linspace(0, 2*np.pi, 50)
    theta_grid, z_grid=np.meshgrid(theta, z)
    x_grid = radius*np.cos(theta_grid) + center_x
    y_grid = radius*np.sin(theta_grid) + center_y
    return x_grid,y_grid,z_grid

Xc,Yc,Zc = data_for_cylinder_along_z(0.2,0.2,0.05,0.1)
ax.plot_surface(Xc, Yc, Zc, alpha=0.5)

plt.show()
