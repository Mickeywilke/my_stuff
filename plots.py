import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import time


##################################

start = time.time()


#cleaning the data
T = 20
time_step = 0.0001
chunk_size = (T / time_step) +1

def split_data(df, chunk_size):
    chunks = []
    for start in range(0, len(df), chunk_size):
        chunk = df.iloc[start:start + chunk_size]
        chunks.append(chunk)
    return chunks

def specific_time(data, time_values):
    final_values = []
    for t in time_values:
        values1 = [] 
        values2 = [] 
        for i in range(len(data)):
            a = data[i]
            values1.append(a.loc[a["t"] == t])
            values1[i] = (np.array(values1)[i])
            values2.append(values1[i][0][1])
        final_values.append(values2)
    return final_values

data_raw = pd.read_csv("process.txt", names = ["t","v", "eta"])
data = split_data(data_raw, int(chunk_size))

###############################################

#exact solution
L = 2
L0 = 0.5
# uniform 1 / (2L)

##############################################

#plotting trajectories 
fig, ax = plt.subplots(3,2)
k = 1 #number of trajectories to plot
t = data[0]["t"]
v = data[0]["v"]
eta = data[0]["eta"]
low_border = 2.9
upp_border = 3
t_1 = data[0][data[0]["t"].between(low_border, upp_border)]["t"]
v_1 = data[0][data[0]["t"].between(low_border, upp_border)]["v"]
eta_1 = data[0][data[0]["t"].between(low_border, upp_border)]["eta"]

low_border2 = 2.92
upp_border2 = 2.93
t_2 = data[0][data[0]["t"].between(low_border2, upp_border2)]["t"]
v_2 = data[0][data[0]["t"].between(low_border2, upp_border2)]["v"]
eta_2 = data[0][data[0]["t"].between(low_border2, upp_border2)]["eta"]

ax[0][0].plot(t, v)
ax[0][1].plot(t, eta)
ax[1][0].plot(t_1, v_1)
ax[1][1].plot(t_1, eta_1)
ax[2][0].plot(t_2, v_2)
ax[2][1].plot(t_2, eta_2)
fig.supxlabel("t")
ax[0][0].hlines(L, 0, T, color = "r")
ax[0][0].hlines(-L, 0, T, color = "r")
ax[0][0].hlines(L0, 0, T, color = "r", ls = ":")
ax[0][0].hlines(-L0, 0, T, color = "r", ls = ":")
ax[1][0].hlines(L0, low_border, upp_border, color = "r", ls = ":")
ax[2][0].hlines(L0, low_border2, upp_border2, color = "r", ls = ":")
#ax[0][0].set_ylabel("v")
#ax[0][1].set_ylabel("\eta")

plt.show()

#############################################

#making the histograms


times = [0.1,1,5, 10, 20] #times at which to plot the density
results = specific_time(data, times)
u = len(times)
v_max =  data_raw["v"].max()
v_min = data_raw["v"].min()
N = int(50) #number of bins
v_values_hist = np.linspace(v_min, v_max, N)
v_values_plot = np.linspace(v_min, v_max, 1000)
delta_v = (v_max - v_min)/N

fig, axes = plt.subplots(u, 1)
fig.suptitle("regular diffusion without drift and reflecting boundaries(small reset)")
fig.subplots_adjust(hspace = 0)
fig.supxlabel("v")
fig.supylabel("P(v,t)")
for i in range(u):
    axes[i].hist(results[i], v_values_hist, density = True, label = "t =" + str(times[i]))
    axes[i].plot(v_values_plot, [1/(2*L) for i in range(len(v_values_plot))], label = "theory")
    axes[i].legend()

end = time.time()
print(f"time taken: {end - start}s")

#plt.show()