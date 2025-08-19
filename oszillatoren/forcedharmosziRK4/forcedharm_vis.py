import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import os



data = pd.read_csv("forcedharmo.txt", names = ["t","x","v"])
t = np.array(data["t"])
x = np.array(data["x"])
v = np.array(data["v"])

plt.plot(t,x, label = "position")
plt.plot(t, v, label = "velocity")
plt.legend()
plt.show()

