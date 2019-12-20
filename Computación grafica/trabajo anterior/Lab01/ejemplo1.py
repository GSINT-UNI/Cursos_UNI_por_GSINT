#ejemplo1.py
# Super Numeros
#import string
#i = input("Por favor ingrese el limite superior ")
#for n in range(i):
#	x= 3*n**3
#	if string.find(str(x), "333")<> -1:
#		print n, " ", x

#fin de programa
import string
print "usando while"
i = input("Por favor ingrese el limite superior")
n = 0
while n <= i:
	x= 3*n**3
	if string.find(str(x), "333")<> -1:
		print n, " ", x
	n=n+1

#4.1.- 

#261   53338743
#462   295833384
#471   313461333
#481   333853923
#558   521223336
#753   1280873331

#4.2.-
#se ingresa un valor n para el cual el programa hara un bucle de 1 a i 
#donde hayara el x = 3*(n)³
#y para cada x encontrar si tiene en sus digitos "333"
#si es asi pues te indica el numero n y el valor de x
#4.3.-
#1- importa la libreria string
#2- indica que el usuario escriba el limite superior y lo guarda en i
#3- el programa realizara un bucle for para n desde 0 hasta el limite superior que se definio antes
#4- se calcula x = 3*(n)³ dentro del bucle
#5- se ejecuta una condicion en donde primero se tranforma x en cadena para buscar si en sus digitos esta la cadena "333"
#6- si cumple la condicion entonces imprimira los valores de n y x

#4.4.-
#los valores que toma string.find son las posiciones donde esta la coincidencia con "333" si no encuentra entonces retornara el valor de -1

#4.5.-

# Super-5
#import string
#i = input("Por favor ingrese el limite superior ")
#for n in range(i):
#	x= 5*n**5
#	if string.find(str(x), "555")<> -1:
#		print n, " ", x
#
#fin de programa

#4.6.-
# Super Numeros usando while
#import string
#print "usando while"
#i = input("Por favor ingrese el limite superior")
#n = 0
#while n <= i:
#	x= 3*n**3
#	if string.find(str(x), "333")<> -1:
#		print n, " ", x
#	n=n+1
#fin de programa