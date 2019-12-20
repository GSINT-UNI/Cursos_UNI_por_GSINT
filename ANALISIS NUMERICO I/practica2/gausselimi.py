## module gaussElimin x = gaussElimin(a,b).
import numpy as np
from numpy import dot

def gaussElimin(a,b):
    n = len(b)
# Elimination phase
    for k in range(0,n-1):
        for i in range(k+1,n):
            if a[i,k] != 0.0:
                lam = a [i,k]/a[k,k]
                a[i,k+1:n] = a[i,k+1:n] - lam*a[k,k+1:n]
                b[i] = b[i] - lam*b[k]
# Back substitution
    for k in range(n-1,-1,-1):
        b[k] = (b[k] - dot(a[k,k+1:n],b[k+1:n]))/a[k,k]
    return b

a = np.array([[3, 4, 2], [9, -1, 0], [2, 1, 1]],'f')

b = np.array([17, 7, 7],'f')

gaussElimin(a,b)