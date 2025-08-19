import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import os
import matplotlib.animation as animation


data = pd.read_csv("pendel.txt", names = ["t","phi","omega"])
t = np.array(data["t"])
phi = np.array(data["phi"])
omega = np.array(data["omega"])
#static plots
plt.plot(t,phi, label = "angle")
plt.legend()
plt.show()
plt.plot(phi, omega, label = "$\omega (\phi)$")
plt.legend()
plt.show()

#animation curve 1
fig, ax = plt.subplots()

angle_curve, = ax.plot(t[0], phi[0])
ax.set_xlim(0, t[-1])
ax.set_ylim(min(phi), max(phi))

def animate1(i):
    angle_curve.set_data(t[:10*i+1], phi[:10*i+1])

ani = animation.FuncAnimation(fig, animate1, frames = len(t), interval = 10)
ffmpeg_writer = animation.FFMpegWriter(fps=30)
plt.show()

#animation curve 2

fig, ax = plt.subplots()

phase_curve, = ax.plot(phi[0], omega[0])
ax.set_xlim(min(phi), max(phi))
ax.set_ylim(min(omega), max(omega))

def animate2(i):
    phase_curve.set_data(phi[:i+1], omega[:i+1])

ani = animation.FuncAnimation(fig, animate2, frames = len(t), interval = 10)
ffmpeg_writer = animation.FFMpegWriter(fps=60)
plt.show()

# create an animation of the pendulum swining with Matplotlib
L = 0.1
def pend_pos(theta):
    return (L*np.sin(theta), -L*np.cos(theta))

fig = plt.figure()
ax = fig.add_subplot(aspect='equal')
ax.set_xlim(1.2*min(pend_pos(phi)[0]), 1.2*max(pend_pos(phi)[0]))
ax.set_ylim(1.2*min(pend_pos(phi)[1]), 1.2*max(pend_pos(phi)[1]))
ax.grid()

x0, y0 = pend_pos(phi[0])
line, = ax.plot([0, x0], [0, y0], lw=2, c='k')
circle = ax.add_patch(plt.Circle(pend_pos(phi[0]), 0.005, fc='r', zorder=3))

def animate3(i):
    x,y = pend_pos(phi[i])
    line.set_data([0, x], [0, y])
    circle.set_center((x, y))

# save a video: 30 fps
ani = animation.FuncAnimation(fig, animate3, frames=len(t), interval = 10)
ffmpeg_writer = animation.FFMpegWriter(fps=30)
plt.show()
