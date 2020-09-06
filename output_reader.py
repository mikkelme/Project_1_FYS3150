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
filename_list = ["output_n" + str(i) + ".txt" for i in range(1, max_exp + 1)]

max_err = np.zeros((len(folder_list), max_exp))
n_space = np.linspace(1, max_exp, max_exp)

for i in range(len(folder_list)):
    for j in range(max_exp):
        if j < 6:
            file = open(folder_list[i] + "/" + filename_list[j], 'r')
            lines = file.readlines()

            #Fill in arrays with data
            n = len(lines)
            x = np.zeros(n-1)
            #u = np.zeros(n-1)
            #f = np.zeros(n-1)
            rel_err = np.zeros(n-1)
            time = float(lines[0].split()[0])
            for k in range(1, n):
                line = lines[k].split()
                x[k-1] = float(line[0])
                #u[k-1] = float(line[1])
                #f[k-1] = float(line[2])
                rel_err[k-1] = float(line[3])
            max_err[i,j] = max(rel_err)
        if max_exp == 7:
            max_err[0,6] = -5.9623200 #Manuel read
            max_err[1,6] = -11.948208 #Manuel read (did vary locally)



    plt.title(folder_list[i])
    plt.plot(n_space ,max_err[i,:], "o")
    plt.xlabel("Log(n)")
    plt.ylabel("Log(Err)")
    plt.show()
