import numpy as np
import matplotlib.pyplot as plt

#Open file
#folder = "LU_decomposition"
folder = "general_solution"
#folder = "special_solution"
filename = "output_n2.txt"

#folder = "Code_example_github"
#filename = "output.txt2"

file = open(folder + "/" + filename, 'r')
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

print(f"Calculating time: {time} mu s")
#Plot

plt.subplot(2,1,1)
plt.plot(x, u, label = "u")
plt.plot(x,f, label = "f")
plt.legend()

plt.subplot(2,1,2)
plt.plot(x, rel_err, label = "rel_err")
plt.legend()
plt.show()
