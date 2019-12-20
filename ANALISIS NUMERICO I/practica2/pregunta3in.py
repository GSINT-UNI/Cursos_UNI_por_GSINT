import sys

def main():
   r0 = 0.994
   p0 = 1
   p1 = 0.497
   q0 = 1
   q1 = 0.497

   print("PRIMER ESQUEMA")
   for k in range (0,50):
     print r0
     r0 = r0/2
   print("decrese a la mitad cada ronda ")
   print
        
   print("SEGUNDO ESQUEMA")
   for k in range (0,30):
     print p0
     print p1
     p0 = 3*p1/2 - p0/2
     p1 = 3*p0/2 - p1/2
   print("converge rapidamente al valor 0.994")
   print
   
   print("TERCER ESQUEMA")
   for k in range (0,100):
     print q0
     print q1
     q0 = 5*q1/2 - q0
     q1 = 5*q0/2 - q1
   print("")  

main()
