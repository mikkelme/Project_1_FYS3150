import numpy as np
import matplotlib as pyplot

n = 4
h = 1/(n+1)

a = np.array(n*[-1])
b = np.array(n*[2])
c = np.array(n*[-1])

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

v = np.ones(n)
f = np.zeros(n)


print(abc[0]*v)
for i in range(n):
    f[i] = (abc[0]*v)/h^2
    v[i+1] = ?

"""
#Step 0
f[0] = (b[0]*v[0] - c[0+1]*v[0+1])/h^2
v[0+1] = (- a[i-1]*v[i-1] + b[i]**v[i] - h**2*f[i])/c[i+1]
for i in range(n):
    f[i] = (- a[i-1]v[i-1] + b[i]*v[i] - c[i+1]*v[i+1])/h^2
    v[i+1] = (- a[i-1]*v[i-1] + b[i]**v[i] - h**2*f[i])/c[i+1]
"""
