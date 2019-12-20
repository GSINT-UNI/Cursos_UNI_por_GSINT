#-*-encoding:utf-8-*-
import scipy.io as sio
import numpy as np 
from numpy import dot
import matplotlib.pyplot as plt
import sys


data = sio.loadmat('hw4data')
# entonces para la ecuacion y=ax^+bx+c donde data['t'] son datos experimentales de 'x' e 'y' es data['y']
# la matriz A es [ (data['t'])^2   (data['t'])    1 ] donde data['t'] es matriz columna R100x1
# El sistema Ax=y no se puede resolver por gauss debido a que A no es cuadrada entonces multiplicamos por la izq por A traspuesta  A^tAx=A^ty

#Construyendo matriz A
A = np.ones((100,1))
A = np.c_[data['t'], data['t']*data['t'], A]

#AHORA multiplico A traspuesta por A y queda una matriz B de 3x3:

B=A.T.dot(A)
print "Matriz A traspuesta por A"
print B
print

#obtenemos a traspuesta por la matriz columna y:
C=A.T.dot(data['y'])
print "Matriz A traspuesta por y"
print C 
print

#Obtenemos un sistema que ya se puede resolver por Gauss: Bx=C


###############################################################
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
    
################################################################

gaussElimin(B,C)
print "Solución para a,b,c:"
print C
print 

plt.plot(data['t'], data['y'])
plt.plot(data['t'], A.dot(C))
plt.show()

#se aprecia la comparacion de los datos experimentales con la grafica probeida por el metodo de solucion de Gauss  

