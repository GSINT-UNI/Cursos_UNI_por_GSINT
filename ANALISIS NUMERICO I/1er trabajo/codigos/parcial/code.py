#Resolviendo:
import numpy as np
from numpy import dot

## module gaussElimin x = gaussElimin(a,b).
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


## module LUdecomp-Doolittle's
def LUdecomp(a):
    n = len(a)
    for k in range(0,n-1):
        for i in range(k+1,n):
            if a[i,k] != 0.0:
                lam = a [i,k]/a[k,k]
                a[i,k+1:n] = a[i,k+1:n] - lam*a[k,k+1:n]
                a[i,k] = lam
    return a

def LUsolve(a,b):
    n = len(a)
    for k in range(1,n):
        b[k] = b[k] - dot(a[k,0:k],b[0:k])
    for k in range(n-1,-1,-1):
        b[k] = (b[k] - dot(a[k,k+1:n],b[k+1:n]))/a[k,k]
    return b



#Resistencias
R = np.array([25., 40., 16., 20., 9., 4., 20.])
r = np.array([0.1, 0.5, 0.0, 0.5, 0.2, 0.0, 0.0])
#Voltajes
E = np.array([12., 10., 0., 12., 24., 0.0, 0.0])
#Corrientes
I = np.array([0.0, 0.0, 0.0])

#Metodo gauss
A = np.array([[-R[0]-r[0]-r[4]-R[3]-R[2], r[4], R[3]], 
              [-r[4],r[4]+r[1]+R[1]+R[5]+R[4], -R[4]], 
              [-R[3], -R[4], R[3]+R[6]+R[3]+R[4]]])

B = np.array([E[0]+E[4], E[4]+E[1], E[3]])
x_g = gaussElimin(A,B)
I_g = np.array([x_g[0], x_g[1]-x_g[0], x_g[1], x_g[0]-x_g[1], x_g[1]-x_g[2], -x_g[2]]) 
print("Metodo Gauss:")
print(I_g)

#Metodo gauss
A = np.array([[-R[0]-r[0]-r[4]-R[3]-R[2], r[4], R[3]], 
              [-r[4],r[4]+r[1]+R[1]+R[5]+R[4], -R[4]], 
              [-R[3], -R[4], R[3]+R[6]+R[3]+R[4]]])

B = np.array([E[0]+E[4], E[4]+E[1], E[3]])
A = LUdecomp(A)
x_LU = LUsolve(A,B)

I_LU = np.array([x_LU[0], x_LU[1]-x_LU[0], x_LU[1], x_LU[0]-x_LU[1], x_LU[1]-x_LU[2], -x_LU[2]]) 
print("Metodo LUdecomp:")
print(I_LU)
