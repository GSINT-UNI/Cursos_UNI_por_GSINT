#metodo punto fijo

import numpy as np
from numpy import linalg as LA

#g   ==> Matriz de funciones
#p0  ==> pto inicial
#tol ==> tolerancia
def pto_fijo(g,p0,tol):
	#if len(g) == 1:
	n = len(g)
	xn = p0
	x0 = np.copy(xn)
	xn1= np.ones_like(x0)
	r = 1.0
	iteraciones = 0
	print("x0: ",p0)
	while(r > tol):
	#while(iteraciones<6):
		iteraciones = iteraciones + 1
		for i in range(n):
			xn1[i] = g[i](xn)
			xn[i] = xn1[i]
		r = LA.norm(xn1-x0)
		print("x",iteraciones,": ",xn1)
		x0 = np.copy(xn1)
	return xn, iteraciones

def g0(x):
	Q = 100.0
	k = 5.97*0.27*2.8
	#K=4.5133
	return (np.sqrt(Q-2*x))*(k/4)**(1/4)
def gp0(x):
	Q = 100.0
	k = 5.97*0.27*2.8
	#K=4.5133
	return ((k/64)**(1/4))*(np.sqrt(Q-2*x))**(-1)

for i in range(50):
	print(gp0(i))

g = np.array([g0])
p0 = np.array([40.0])
resultado = pto_fijo(g,p0,0.000001)
print (resultado)
print (g0(resultado[0]))
