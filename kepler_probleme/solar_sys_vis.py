import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import matplotlib.animation as animation


data = pd.read_csv("C:\\msys64\\ucrt64\\bin\\solar_system.txt", 
        names = ["t","x1","y1","x2","y2","x3", "y3","x4","y4","x5","y5",
                 "x6","y6","x7","y7","x8","y8"])
t = np.array(data["t"])
x1 = np.array(data["x1"])
y1 = np.array(data["y1"])
x2 = np.array(data["x2"])
y2 = np.array(data["y2"])
x3 = np.array(data["x3"])
y3 = np.array(data["y3"])
x4 = np.array(data["x4"])
y4 = np.array(data["y4"])
x5 = np.array(data["x5"])
y5 = np.array(data["y5"])
x6 = np.array(data["x6"])
y6 = np.array(data["y6"])
x7 = np.array(data["x7"])
y7 = np.array(data["y7"])
x8 = np.array(data["x8"])
y8 = np.array(data["y8"])


plt.plot(x1,y1)
plt.plot(x2,y2)
plt.plot(x3,y3)
plt.plot(x4,y4)
plt.plot(x5,y5)
plt.plot(x6,y6)
plt.plot(x7,y7)
plt.plot(x8,y8)
plt.show()

fig, ax = plt.subplots()
curve1, = ax.plot(x1[0], y1[0], color ='b')
mass1 = ax.add_patch(plt.Circle((x1[0], y1[0]), radius = 0.2, label = 'merkur',color ='b'))
curve2, = ax.plot(x2[0], y2[0],color ='g')
mass2 = ax.add_patch(plt.Circle((x2[0], y2[0]), radius = 0.2, label = 'venus',color ='g'))
curve3, = ax.plot(x3[0], y3[0], color ='r')
mass3 = ax.add_patch(plt.Circle((x3[0], y3[0]), radius = 0.2, label = 'erde', color ='r'))
curve4, = ax.plot(x4[0], y4[0],color ='c')
mass4 = ax.add_patch(plt.Circle((x4[0], y4[0]), radius = 0.2, label = 'mars', color ='c'))
curve5, = ax.plot(x5[0], y5[0], color ='m')
mass5 = ax.add_patch(plt.Circle((x5[0], y5[0]), radius = 0.2, label = 'jupiter', color ='m'))
curve6, = ax.plot(x6[0], y6[0], color ='y')
mass6 = ax.add_patch(plt.Circle((x6[0], y6[0]), radius = 0.2, label = 'saturn', color ='y'))
curve7, = ax.plot(x7[0], y7[0], color ='k')
mass7 = ax.add_patch(plt.Circle((x7[0], y7[0]), radius = 0.2, label = 'uranus', color ='k'))
curve8, = ax.plot(x8[0], y8[0], color ='violet')
mass8 = ax.add_patch(plt.Circle((x8[0], y8[0]), radius = 0.2, label = 'neptun', color ='violet'))

plt.legend()
ax.set_xlim(-32,32)
ax.set_ylim(-32,32)
def animate1(i):
    i = i
    curve1.set_data(x1[:i], y1[:i])
    curve2.set_data(x2[:i], y2[:i])
    curve3.set_data(x3[:i], y3[:i])
    curve4.set_data(x4[:i], y4[:i])
    j = i
    curve5.set_data(x5[:j], y5[:j])
    curve6.set_data(x6[:j], y6[:j])
    curve7.set_data(x7[:j], y7[:j])
    curve8.set_data(x8[:j], y8[:j])

    mass1.set_center((x1[i], y1[i]))
    mass2.set_center((x2[i], y2[i]))
    mass3.set_center((x3[i], y3[i]))
    mass4.set_center((x4[i], y4[i]))
    mass5.set_center((x5[j], y5[j]))
    mass6.set_center((x6[j], y6[j]))
    mass7.set_center((x7[j], y7[j]))
    mass8.set_center((x8[j], y8[j]))


ani = animation.FuncAnimation(fig, animate1, frames = len(x1), interval = 1)
ffmpeg_writer = animation.FFMpegWriter(fps=30)
plt.show()



























