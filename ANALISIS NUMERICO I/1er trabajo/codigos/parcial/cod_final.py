import numpy as np
from numpy import linalg as LA
from numpy import dot
import numpy as np
from math import sqrt

#Norma infinita de una matriz
def norm_inf(a):
    n = len(a)
    s = [0.0]*n
    
    for k in range(n):
        s[k] = sum([abs(x) for x in a[k][0:n]])
    
    return max(s)
#inversa de la matriz
def inv_m(a):
    n = len(a)
    a_inv = np.identity(n)
    
    for k in range(n):
        d = a[k,k]
        a[k,0:n] = a[k,0:n]/d
        a_inv[k,0:n] = a_inv[k,0:n]/d
        
        for j in range(k+1,n):
            lam = a[j,k]/a[k,k]
            a_inv[j,0:n] = a_inv[j,0:n] - lam*a_inv[k,0:n]
            a[j,0:n] = a[j,0:n] - lam*a[k,0:n]
            
    for k in range(n-1,-1,-1):
        for j in range(k-1,-1,-1):
            d = a[j,k]
            a[j,0:n] = a[j,0:n]-d*a[k,0:n]
            a_inv[j,0:n] = a_inv[j,0:n]-d*a_inv[k,0:n]
    return a_inv

#numero de condicion de una matriz
def cond_m_inf(a):
    return norm_inf(a)*norm_inf(inv_m(a))

def prodint(u,v):
    n = len(u)
    p = 0
    for k in range(n):
        p = p + u[k]*v[k]
    return p


#Metodo Coleski-----------------------------------------
def choleski(a):
    n = len(a)
    for k in range(n):
        try:
            a[k,k] = sqrt(a[k,k] - a[k,0:k]@a[k,0:k])
        except ValueError:
            error.err("No es matriz positiva")
        for i in range(k+1,n):
            a[i,k] = (a[i,k] - a[i,0:k]@a[k,0:k])/a[k,k]
    for k in range(1,n): a[0:k,k] = 0.0
    return a

def choleskiSol(L,b):
    n = len(b)
    # Solution of [L]{y} = {b}
    for k in range(n):
        b[k] = (b[k] - L[k,0:k]@b[0:k])/L[k,k]
    # Solution of [L_transpose]{x} = {y}
    for k in range(n-1,-1,-1):
        b[k] = (b[k] - L[k+1:n,k]@b[k+1:n])/L[k,k]
    return b
#-------------------------------------------------------

#Metodo eliminacion de Gauss----------------------------
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
        b[k] = (b[k] - a[k,k+1:n]@b[k+1:n])/a[k,k]
    return b
#-------------------------------------------------------


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



a_g= np.array([[-61.3, 0.2, 20.0], [-0.2, 53.7, 9.0], [-20.0, -9.0, -49.5]])
print(cond_m_inf(np.copy(a_g)))

b_g = np.array([36.0, 34.0, 12.0])
print("aaa",inv_m(np.copy(a_g))@b_g)

print("resultado:")
print(gaussElimin(np.copy(a_g),np.copy(b_g)))

a_g= np.array([[61.3, -0.2, -20.0], [-0.2, 53.7, 9.0], [-20.0, -9.0, -49.5]])
b_g = np.array([-36.0, 34.0, 12.0])
print(cond_m_inf(np.copy(a_g)))
print("resultado:")
LUsolve(LUdecomp(np.copy(a_g)),np.copy(b_g))