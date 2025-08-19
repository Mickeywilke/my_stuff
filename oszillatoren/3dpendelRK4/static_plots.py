import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import matplotlib.animation as animation
import tkinter
import tkinter.messagebox




data = pd.read_csv("3dpendel.txt", names = ["t","phi1","phi2","omega1","omega2"])
t = np.array(data["t"])
phi1 = np.array(data["phi1"])
phi2 = np.array(data["phi2"])
omega1 = np.array(data["omega1"])
omega2 = np.array(data["omega2"])

#static plots
plt.plot(t,phi1, label = "angle1")
plt.plot(t, phi2, label = "angle2")
plt.legend()
plt.show()
plt.plot(phi1, omega1, label = "$\omega (\phi_1)$")
plt.plot(phi2, omega2, label = "$\omega (\phi_2)$")
plt.legend()
plt.show()
