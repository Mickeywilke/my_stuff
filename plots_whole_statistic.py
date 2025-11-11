import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import time
from scipy.fft import rfft, irfft, rfftfreq, ifftshift, fft, fftshift, fftfreq


##################################

start = time.time()


#cleaning the maindata
T = 1000
time_step = 0.01
D = 0.1 #diffusion
L = 10 #half the length
L0 = 0.25 # ROI
n = 10 #number of particles for each eta calculation(simulation) must be a divisor of the number of trajectories
chunk_size = int(T / time_step +1)

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

def split_data_eta(df, chunk_size):
    chunks = []
    for i in range(0, len(df), chunk_size):
        chunks.append(df[i: (i + chunk_size)])
    return chunks

def get_eta_total(data):
    values = []
    for j in range(len(data)):
        clean_data = []
        for i in range(len(data[j])):
            clean_data.append(data[j][i]["eta"])
        clean_data = np.array([clean_data[i] for i in range(len(clean_data))])
        a = np.ones_like(clean_data[0])
        for i in range(len(clean_data)):
            a = np.multiply(clean_data[i], a)
        values.append(a)
    return(values)

data_raw = pd.read_csv("process_wholestat.txt", names = ["t","v", "eta"])
data = split_data(data_raw, int(chunk_size))
data = split_data_eta(data, n)
data = get_eta_total(data)

#fourier transforming the data
N = int(T / time_step) 
f_data = []
mean = (1 - L0 / L)
for i in range(len(data)):
    eta = data[i] - mean**(n)#(minus the mean usually but not in this case since we calculate corrlation function with the mean in it)
    eta_f = time_step * rfft(eta)
    f_data.append(eta_f)
f = rfftfreq(N, time_step)

#calculate power spectrum

def variance(data):
    a = np.zeros_like(data)
    for i in range(len(data)):
        a[i] = np.real(data[i] * np.conjugate(data[i]))
    s = np.zeros_like(a[0])
    for i in range(len(a)):
        s+= a[i]
    return s / len(data)

S = variance(f_data) / T

#calculate correlation function(inverse fourier transform)
c = irfft(S) / time_step 

#analytic functions

k = 100
def power_spec(correlation_function):
    power = time_step * rfft(correlation_function)
    #power *= np.exp(-1j * f * T/2)
    return np.real(power)

def power_spec2(f):
    f = 2 * np.pi * f #formula in angular frequency
    alpha = np.sqrt(1j * f / D)
    numerator =  alpha * np.sinh(alpha * L0) * np.sinh(alpha * (L - L0))
    denominator = np.sinh(alpha * L)
    pre = 2 * D / (f**2 * L)
    return pre * np.real(numerator / denominator)

def sum_function(tau):
    a = 0
    for i in range(1,k+1):
        a += (np.sin(i * np.pi * L0 / L))**2 * np.exp(- D * (i * np.pi / L )**2 * np.abs(tau) ) / (i**2)
    return a

def corr_func(tau):
    return 2 / (np.pi**2) * sum_function(tau)

def autocorr(tau):
    return (corr_func(tau) + mean**2)**n -  mean**(2*n)





#plot everything 

fig, ax = plt.subplot_mosaic([['left', 'right'],['bottom', 'bottom']], constrained_layout=True)
times1 = np.linspace(0, T, chunk_size)[:-1]
ax['bottom'].scatter(times1, c, s=1, label = "sims")
ax['bottom'].plot(times1, autocorr(times1), color = "r", label = "theory")

ax['bottom'].set_title("Correlation function")
ax['bottom'].set_xlabel("time")
ax['bottom'].legend(loc = "upper right")
ax['bottom'].set_xlim(0,10)


ax["left"].plot(f, f_data[0])
ax["left"].set_xlabel("frequency")
ax["left"].set_title("fourier transform")
ax["left"].set_xlim(0,10)

times2 = np.linspace(0, T/2, int(T/time_step))
f2 = rfftfreq(int(T/time_step), time_step)

ax["right"].loglog(f, S, label = "sims")
ax["right"].loglog(f2, np.real(time_step*rfft(corr_func(times2))), color = "r", label = "theory")
ax["right"].loglog(f, power_spec2(f), color = "g", label = "theory2")
ax["right"].set_xlim(0,10)
ax["right"].set_xlabel("frequency")
ax["right"].set_title("power spectrum")
#ax["right"].set_ylim(10**(-5),1)
ax['right'].legend(loc = "upper right")

end = time.time()
print(f"time taken: {end - start}s")
plt.savefig("C:/Users/Hagener NR.190385/Desktop/c-tests/master/graphs/statistics_whole.png")

plt.show()