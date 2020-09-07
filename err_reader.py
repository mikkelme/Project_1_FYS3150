import numpy as np
import matplotlib.pyplot as plt



max_exp = 4
folder_list = ["general_solution", "special_solution", "LU_decomposition"]
#folder_list = ["general_solution", "special_solution"]
filename_list = ["max_err_n" + str(i) for i in range(1, max_exp + 1)]
N = len(folder_list)

max_err = np.zeros((N, max_exp))
n_space = np.linspace(1, max_exp, max_exp)

for i in range(N):
    for j in range(max_exp):
        file = open(folder_list[i] + "/" + filename_list[j], 'r')
        lines = file.readlines()
        max_err[i,j] = lines[0]



fig, axes = plt.subplots(ncols=1, nrows=N, figsize=(8,10))
plt.subplots_adjust(hspace=0.35, bottom=0.08, top=0.94)

for i in range(N):
    plt.subplot(N, 1, i+1)
    plt.title(folder_list[i])
    plt.plot(n_space ,max_err[i], "o")
    plt.xlabel("Log(n)")
    plt.ylabel("Log(Err)")
plt.show()
