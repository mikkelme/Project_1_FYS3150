import numpy as np
import matplotlib.pyplot as plt

#Open file
#folder = "LU_decomposition"
#folder = "general_solution"
#folder = "special_solution"
#filename = "output_n2.txt"

#folder = "Code_example_github"
#filename = "output.txt2"

max_exp = 5
folder_list = ["general_solution", "special_solution"] #, "LU_decomposition"]
filename_list = ["max_err_n" + str(i) for i in range(1, max_exp + 1)]
N = len(folder_list)

max_err = np.zeros((N, max_exp))
n_space = np.linspace(1, max_exp, max_exp)

for i in range(N):
    for j in range(max_exp):
        file = open(folder_list[i] + "/" + filename_list[j], 'r')
        lines = file.readlines()
        max_err[i,j] = lines[0]



for i in range(N):
    plt.subplot(N, 1, i+1)
    plt.title(folder_list[i])
    plt.plot(n_space ,max_err[i], "o")
    plt.xlabel("Log(n)")
    plt.ylabel("Log(Err)")
plt.show()
