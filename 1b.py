import numpy as np
import matplotlib.pyplot as plt

n = 100
h = 1/(n+1)

a = np.array(n*[-1])/h**2
b = np.array(n*[2])/h**2
c = np.array(n*[-1])/h**2

a[0] = 0; c[-1] = 0


u = np.zeros(n)
u[0] = 0
u[-1] = 0


def f(x):
    return 100*np.exp(-10*x)

def analytic(x):
    return 1 - (1 - np.exp(-10))*x - np.exp(-10*x)

x = np.linspace(0,1,n)
f = f(x)


#Forward substitution
b_tilde = np.zeros(n)
f_tilde = np.zeros(n)
b_tilde[0] = b[0]
f_tilde[0] = f[0]

for i in range(1,n):
    b_tilde[i] = b[i] - a[i]*c[i-1]/b_tilde[i-1]
    f_tilde[i] = f[i] - a[i]*f_tilde[i-1]/b_tilde[i-1]


#Backward substitution
#u[-1] = f_tilde[-1]/b_tilde[-1]
for j in range(1 , n):
    i = n-j
    u[i-1] = (f_tilde[i-1] - c[i-1]*u[i])/b_tilde[i-1]
u[0] = 0

plt.plot(x, u, label = "numerical")
plt.plot(x, analytic(x), label = "analytical")
plt.legend()
plt.show()






"""
abc = np.zeros((n,n))
#fill in abc-array
for i in range(n):
    for j in range(n):
        if i == j + 1:
            abc[i,j] = a[j]
        if i == j:
            abc[i,j] = b[i]
        if i == j - 1:
            abc[i,j] = c[i]
"""
