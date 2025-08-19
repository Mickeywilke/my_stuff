import vpython
from vpython import *
import numpy as np
import pandas as pd



ball1 = vpython.sphere(color = color.green, radius = 0.1, make_trail=True, retain = 1000)
rod1 = cylinder(pos=vector(0,0,0),axis=vector(0,1,0), radius=0.01)
base  = box(pos=vector(0,-4.25,0),axis=vector(1,0,0),
            size=vector(10,0.5,10) )
s1 = cylinder(pos=vector(0,-3.99,0),axis=vector(0,-0.1,0), radius=0.8, color=color.gray(luminance=0.7))

data = pd.read_csv("3dpendel.txt", names = ["t","phi1","phi2","omega1","omega2"])
t = np.array(data["t"])
phi1 = np.array(data["phi1"])
phi2 = np.array(data["phi2"])
omega1 = np.array(data["omega1"])


def get_pos(L, phi, theta):
    x = L*np.sin(theta)*np.cos(phi)
    y = L*np.sin(phi)*np.sin(theta)
    z = L*(- np.cos(theta))
    return (x, y, z)

(x1, y1, z1) = get_pos(3, phi1, phi2)

i = 0
while True:
    rate(600)
    i = i + 1
    i = i % len(x1)
    ball1.pos = vector(x1[i], z1[i], y1[i])
    rod1.axis = vector(x1[i], z1[i], y1[i])
    s1.pos = vector(x1[i], -3.99, y1[i])
