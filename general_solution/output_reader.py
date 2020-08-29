import numpy as np
import matplotlib.pyplot as plt

#Open file
filename = "output_file"
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
    x[i] = float(line[0])
    u[i] = float(line[1])
    f[i] = float(line[2])
    rel_err[i] = float(line[3])

#Plot
plt.plot(x, rel_err)
plt.show()
