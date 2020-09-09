import numpy as np
import matplotlib.pyplot as plt


max_exp = 2
folder_list = ["general_solution", "special_solution"] #, "LU_decomposition"]
#folder_list = ["special_solution"]
filename_list = ["output_n" + str(i) + ".txt" for i in range(1, max_exp + 1)]


N = len(folder_list)
X = []
F = []
V = []
ERR = []
for i in range(N):
    X.append([])
    F.append([])
    V.append([])
    ERR.append([])


np.zeros((N, max_exp))


for i in range(N):
    for j in range(max_exp):
        file = open(folder_list[i] + "/" + filename_list[j], 'r')
        lines = file.readlines()

        #Fill in arrays with data
        n = len(lines)
        x = np.zeros(n-1)
        v = np.zeros(n-1)
        f = np.zeros(n-1)
        rel_err = np.zeros(n-1)
        time = float(lines[0].split()[0])
        for k in range(1, n):
            line = lines[k].split()
            x[k-1] = float(line[0])
            v[k-1] = float(line[1])
            f[k-1] = float(line[2])
            rel_err[k-1] = float(line[3])
        X[i].append(x)
        F[i].append(f)
        V[i].append(v)
        ERR[i].append(rel_err)


if False:
    for j in range(max_exp):
        fig, axes = plt.subplots(ncols=N, nrows=2, figsize=(10,8))
        plt.subplots_adjust(left = 0.10, bottom = 0.08, right = 0.96, top = 0.94, wspace = 0.29, hspace = 0.28)
        for i in range(N):
            plt.subplot(2,N,i+1)
            plt.title(folder_list[i] + ",n = " + str(j+1))
            plt.plot(X[i][j], F[i][j], label = "Analytical")
            plt.plot(X[i][j], V[i][j], label = "Numerical")
            plt.xlabel("x")
            plt.ylabel("y")
            plt.legend()

            plt.subplot(2,N,i+3)
            plt.title(folder_list[i] + ",n = " + str(j+1))
            plt.plot(X[i][j], ERR[i][j], label = "rel_err")
            plt.xlabel("x")
            plt.ylabel("log10(error)")
            plt.legend()
        plt.show()

if True:
    i = 1
    plt.title("Special Algorithm: Numerical vs Analytical")
    plt.xlabel("x")
    plt.ylabel("y")

    for j in range(max_exp):
        plt.plot(X[i][j], V[i][j], label = f"Numerical (h = {10**(-(j+1))})")
    plt.plot(X[i][j], F[i][j],  label = f"Analytical")
    plt.legend()
    plt.show()
