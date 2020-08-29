import numpy as np
import matplotlib.pyplot as plt

#Open file
filename = "sp_output_file.txt"
file = open(filename, 'r')
lines = file.readlines()

#Fill in arrays with data
n = len(lines)
x = np.zeros(n)
u = np.zeros(n)
f = np.zeros(n)
rel_err = np.zeros(n)
for i in range(n):
    line = lines[i].split()
    x[i] = float(line[0]) # x = [0, 0.01, ... 0.99]
    u[i] = float(line[1]) # approx
    f[i] = float(line[2]) # exact
    rel_err[i] = float(line[3]) # log10 relative error

#Plot
plt.plot(x, u, label='approx')
plt.plot(x, f,label='exact')
plt.legend()
plt.show()
