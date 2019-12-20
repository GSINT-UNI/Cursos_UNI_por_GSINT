
import numpy as np 
import matplotlib.pyplot as plt
import sys

def main():

   it = np.linspace(0,49,50)
   R = np.array([],dtype='float')
   r0 = 0.994 
   
   P = np.array([],dtype='float')
   p0 = 1
   p1 = 0.497
  
   
   Q = np.array([],dtype='float')
   q0 = 1
   q1 = 0.497
  

   print("PRIMER ESQUEMA")
   for k in range (0,50):
     Rerror = pow(0.5,k) - r0
     R = np.append(R,Rerror)
     print Rerror
     r0 = r0/2
   print("decrese a la mitad cada ronda ")
     
   plt.plot(it, R)
   plt.show()
   
   
        
   print("SEGUNDO ESQUEMA")
   for k in range (0,25):
     Perror0 = pow(0.5,k) - p0 
     Perror1 = pow(0.5,k+1) - p1
     P = np.append(P,Perror0)
     P = np.append(P,Perror1)  
     print Perror0
     print Perror1
     p0 = 3*p1/2 - p0/2
     p1 = 3*p0/2 - p1/2
   print("converge rapidamente al valor 0.994")
   print 
   
   plt.plot(it, P)
   plt.show()
   #plt.savefig('esquema2.png')
   
   print("TERCER ESQUEMA")
   for k in range (0,25):
     Qerror0 = pow(0.5,k) - q0
     Qerror1 = pow(0.5,k+1) - q1
     Q = np.append(Q,Qerror0)
     Q = np.append(Q,Qerror1)
     print Qerror0
     print Qerror1
     q0 = 5*q1/2 - q0
     q1 = 5*q0/2 - q1
   print("")  
   
   plt.plot(it, Q)
   plt.show()
   #plt.savefig('esquema3.png')

main()
