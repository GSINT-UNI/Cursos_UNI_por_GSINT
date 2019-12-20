import matplotlib.pyplot as plt
import numpy as np
from numpy import linalg as LA

K = float(5.97*0.27*2.8) #CONSTANTE DE EQUILIBRIO
Q = 100 #CONCENTRACION INICIAL Q
a=4*K
b=4*K*Q
c=K*Q*Q
print(K,a,b,c)
#funcion
def f(x):
    R = 4.0*x**4 - a*x**2 + b*x - c
    return R
#funcion derivada
def g(x):
    s = (16.0*(x**3)) - (2.0*a*x) + (4.0*K*Q)
    return s

def NEWTON(k): 
    x = k   
    
    tolerancia = 10.0**(-6.0)
    while(abs(f(x)/g(x))>tolerancia):  
    	
        x = x - f(x)/g(x)                              
    return x

print("final: ",NEWTON(5.0))

x = np.linspace(-10, 10, num = 100)
fx = f(x)

plt.plot(x, fx,'-')
plt.show()

    
