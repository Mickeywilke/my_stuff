import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import matplotlib.animation as animation
import tkinter
import tkinter.messagebox



# create an animation of the pendulum swining with Matplotlib
x1, y1, x2, y2, x3, y3, L1vec, L2vec, L3vec = np.loadtxt('trippelpendelpos.txt')
L1 = L1vec[0]
L2 = L2vec[0]
L3 = L3vec[0]

fig = plt.figure()
ax = fig.add_subplot(aspect='equal')
ax.grid()
totl = L1 + L2 + L3
ax.set_xlim(-totl -totl/10, totl + totl/10)
ax.set_ylim(-totl -totl/10, totl + totl/10)

x10, y10 = x1[0], y1[0]
x20, y20 = x2[0], y2[0]
x30, y30 = x3[0], y3[0]


line1, = ax.plot([0, x10], [0, y10], lw=2, c='k')
line2, = ax.plot([x10, x20], [y10, y20], lw=2, c='k')
line3, = ax.plot([x20, x30], [y20, y30], lw=2, c='k')
circle1 = ax.add_patch(plt.Circle([x10,y10], 0.05, fc='r', zorder=3))
circle2 = ax.add_patch(plt.Circle([x20, y20], 0.05, fc='r', zorder=3))
circle3 = ax.add_patch(plt.Circle([x30, y30], 0.05, fc='r', zorder=3))





def animate3(i):
    line1.set_data([0, x1[i]], [0, y1[i]])
    line2.set_data([x1[i], x2[i]], [y1[i], y2[i]])
    line3.set_data([x2[i], x3[i]], [y2[i], y3[i]])

    circle1.set_center((x1[i], y1[i]))
    circle2.set_center((x2[i], y2[i]))
    circle3.set_center((x3[i], y3[i]))

    if i == len(x1)-1:
        restart()



# save a video: 30 fps
ani = animation.FuncAnimation(fig, animate3, frames=len(x1), interval = 1, repeat = False)
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
