import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import matplotlib.animation as animation
import tkinter
import tkinter.messagebox




data = pd.read_csv("doppelpendel.txt", names = ["t","phi1","phi2","omega1","omega2"])
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

#animation angles
fig, ax = plt.subplots()

angle_curve1, = ax.plot(t[0], phi1[0])
angle_curve2, = ax.plot(t[0], phi2[0])

ax.set_xlim(0, t[-1])
ax.set_ylim(min(phi1), max(phi1))

def animate1(i):
    angle_curve1.set_data(t[:10*i+1], phi1[:10*i+1])
    angle_curve2.set_data(t[:10*i+1], phi2[:10*i+1])

ani = animation.FuncAnimation(fig, animate1, frames = len(t), interval = 20)
ffmpeg_writer = animation.FFMpegWriter(fps=30)
plt.show()

#animation phase space
fig, ax = plt.subplots()

angle_curve1, = ax.plot(phi1[0], omega1[0])
angle_curve2, = ax.plot(phi2[0], omega2[0])

ax.set_xlim(min(phi1), max(phi1))
ax.set_ylim(min(omega1), max(omega1))

def animate1(i):
    angle_curve1.set_data(phi1[:10*i+1], omega1[:10*i+1])
    angle_curve2.set_data(phi2[:10*i+1], omega2[:10*i+1])

ani = animation.FuncAnimation(fig, animate1, frames = len(t), interval = 30)
ffmpeg_writer = animation.FFMpegWriter(fps=30)
plt.show()

# create an animation of the pendulum swining with Matplotlib
L1 = 1
L2 = 1
def pend_pos1(phi1):
    return np.array((L1*np.sin(phi1), -L1*np.cos(phi1)))
def pend_pos2(phi1, phi2):
    return pend_pos1(phi1) + np.array((L2*np.sin(phi2), -L2*np.cos(phi2)))

fig = plt.figure()
ax = fig.add_subplot(aspect='equal')
ax.grid()
totl = L1 + L2
ax.set_xlim(-totl -totl/10, totl + totl/10)
ax.set_ylim(-totl -totl/10, totl + totl/10)

x10, y10 = pend_pos1(phi1[0])
x20, y20 = pend_pos2(phi1[0], phi2[0])

line1, = ax.plot([0, x10], [0, y10], lw=2, c='k')
line2, = ax.plot([x10, x20], [y10, y20], lw=2, c='k')
circle1 = ax.add_patch(plt.Circle(pend_pos1(phi1[0]), 0.05, fc='r', zorder=3))
circle2 = ax.add_patch(plt.Circle(pend_pos2(phi1[0], phi2[0]), 0.05, fc='r', zorder=3))




def animate3(i):
    x1,y1 = pend_pos1(phi1[i])
    x2,y2 = pend_pos2(phi1[i], phi2[i])
    line1.set_data([0, x1], [0, y1])
    line2.set_data([x1, x2], [y1, y2])
    circle1.set_center((x1, y1))
    circle2.set_center((x2, y2))
    if i == len(t)-1:
        restart()



# save a video: 30 fps
ani = animation.FuncAnimation(fig, animate3, frames=len(t), interval = 10, repeat = False)
ffmpeg_writer = animation.FFMpegWriter(fps=30)
def restart():
    root = tkinter.Tk()
    root.withdraw()
    result = tkinter.messagebox.askyesno("Restart", "Do you want to restart animation?")
    if result:
        ani.frame_seq = ani.new_frame_seq() 
    else:
        plt.close()

plt.show()
