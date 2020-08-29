import numpy as np
import matplotlib.pyplot as plt

n = 100
h = 1/(n+1)


d = np.array(n*[2])
e = np.array(n*[-1])

#e[0] = 0; e[-1] = 0


u = np.zeros(n)
u[0] = 0
u[-1] = 0


def f(x):
    return 100*np.exp(-10*x)

def analytic(x):
    return 1 - (1 - np.exp(-10))*x - np.exp(-10*x)

x = np.linspace(0,1,n)
f = f(x)


d_tilde = np.zeros(n)
f_tilde = np.zeros(n)

d_tilde[0] = d[0]
f_tilde[0] = f[0]

for i in range(1, n):
    d_tilde[i] = (i + 1)/i
    f_tilde[i] = f[i] + ((i - 1)*f_tilde[i-1])/i


#Backward substitution
for j in range(1 , n):
    i = n-j
    u[i-1] = (i - 1)/i*(f_tilde[i-1] + u[i])
u[0] = 0
u = u*h**2

plt.plot(x, u, label = "numerical")
plt.plot(x, analytic(x), label = "analytical")
plt.legend()
plt.show()
