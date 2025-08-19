import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import matplotlib.animation as animation


data = pd.read_csv("2_body.txt", names = ["t","x1","y1","x2","y2"])
t = np.array(data["t"])
x1 = np.array(data["x1"])
y1 = np.array(data["y1"])
x2 = np.array(data["x2"])
y2 = np.array(data["y2"])

plt.plot(x1, y1)
plt.plot(x2, y2)
plt.show()

#animation
fig, ax = plt.subplots()
ax.set_aspect('equal')

angle_curve1, = ax.plot(x1[0], y1[0], label = 'first mass')
mass1 = ax.add_patch(plt.Circle((x1[0], y1[0]), radius = 0.1))
angle_curve2, = ax.plot(x2[0], y2[0], label = 'second mass')
mass2 = ax.add_patch(plt.Circle((x2[0], y2[0]), radius = 0.05))

plt.legend()
ax.set_xlim(min(min(x1),min(x2)), max(max(x1), max(x2)))
ax.set_ylim(min(min(y1),min(y2)), max(max(y1),max(y2)))

def animate1(i):
    i = 10*i
    angle_curve1.set_data(x1[:i], y1[:i])
    angle_curve2.set_data(x2[:i], y2[:i])
    mass1.set_center((x1[i], y1[i]))
    mass2.set_center((x2[i], y2[i]))

ani = animation.FuncAnimation(fig, animate1, frames = len(x1), interval = 1)
ffmpeg_writer = animation.FFMpegWriter(fps=30)
plt.show()

