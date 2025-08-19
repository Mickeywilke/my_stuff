import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

data = pd.read_csv("harmoszidata.txt", names = ["t","x","v"])
t = np.array(data["t"])
x = np.array(data["x"])
v = np.array(data["v"])

print(t)

plt.plot(t,x)
plt.plot(t, v)
plt.show()


