import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

data = pd.read_csv("C:\\msys64\\ucrt64\\bin\\2_3dbody.txt", names = ["t","x1","y1","z1","x2","y2", "z2"])
t = np.array(data["t"])
x1 = np.array(data["x1"])
y1 = np.array(data["y1"])
z1 = np.array(data["z1"])

x2 = np.array(data["x2"])
y2 = np.array(data["y2"])
z2 = np.array(data["z2"])



ax = plt.figure().add_subplot(projection='3d')
ax.plot(x1, y1, z1)
ax.plot(x2, y2, z2)


