import numpy as np
import matplotlib.pyplot as plt

#Open file
filename = "output_n2.txt"
file = open(filename, 'r')
lines = file.readlines()

#Fill in arrays with data
n = len(lines)
x = np.zeros(n-1)
u = np.zeros(n-1)
f = np.zeros(n-1)
rel_err = np.zeros(n-1)
time = float(lines[0].split()[0])
for i in range(1, n):
    line = lines[i].split()
    x[i-1] = float(line[0])
    u[i-1] = float(line[1])
    f[i-1] = float(line[2])
    rel_err[i-1] = float(line[3])

print(time)
#Plot
plt.plot(x, rel_err)
plt.show()
