import numpy as np
import matplotlib.pyplot as plt
import os.path

#Path settings
max_exp = 7
folder_list = ["general_solution", "special_solution", "LU_decomposition"]
title = ["General algorithm", "Special algorithm", "LU decomposition"]
filename_list = ["max_err_n" + str(i) for i in range(1, max_exp + 1)]

#Extract information
N = len(folder_list)
max_err = np.zeros((N, max_exp))
n_space = np.linspace(1, max_exp, max_exp)
h_space = 1/10**n_space



for i in range(N):
    for j in range(max_exp):
            path = folder_list[i] + "/" + filename_list[j]
            if os.path.isfile(path):
                file = open(path, 'r')
                lines = file.readlines()
                max_err[i,j] = lines[0]
            else:
                max_err[i,j] = np.nan


#Plot
fig, axes = plt.subplots(ncols=1, nrows=N, figsize=(8,10))
plt.subplots_adjust(left=0.08, bottom=0.06, right = 0.98, top=0.97, hspace=0.35)
color = ["tab:blue", "tab:green", "tab:red"]
for i in range(N):
    plt.subplot(N, 1, i+1)
    plt.title(title[i])
    plt.plot(h_space ,max_err[i], "o", color = color[i])
    for a,b in (zip(h_space, max_err[i])):
        plt.text(a*1.3, b, "{:2.2f}".format(b))
    plt.xscale("log")
    plt.xlim(0.5e-7,4e-1)
    plt.ylim(-11,0)
    plt.xlabel("h")
    plt.ylabel(r"log10($\epsilon$)")
plt.show()
