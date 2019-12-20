# Ejemplo de  Programa con  OPENGL 
# ejemplo2.py

#las siguientes 3 lineas sirven para importar 
#todas las funciones de los modulos GL, GLU y GLUT

from OpenGL.GLUT import *
from OpenGL.GL import *
from OpenGL.GLU import *
# la siguiente linea provee las herramientas para el manejo de graficas
import sys

#Las primeras letras de los comandos indican a que modulo
#pertenecen ej: gl, glu, glut

#def - indica el inicio de un nuev bloque de codigo
def draw():
	glClear(GL_COLOR_BUFFER_BIT)
#	glutWireTeapot(0.7) 
#	glutWireSphere(0.5, 25, 7)
	glutWireCube(1.0)
	glFlush() # Presenta el dibujo en la pantalla

#Presentaremos Graficos en estilo GLUT 
#GLUT - GL Utilities Toolkit
#Provee los calculos para manejar multiples plataformas
#Windows, Mac, Linux

#sys.argv - permite ingresar parametros por consola, 
# si fuera necesario
glutInit(sys.argv) 

#Utilizaremos un solo buffer de display - SINGLE
# Y Utilizaremos el esquema de color RGB 
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB)
glutInitWindowSize(800, 800)
glutInitWindowPosition(20, 20)
glutCreateWindow("Mi primer Programa OPENGL")

#indicamos a GLUT donde encontramos la funcion
#que crea la escena Grafica en este caso - draw
glutDisplayFunc(draw)

#la siguiente funcion permite correr el programa 
#en un loop continuo. Permite a GLUT chequear
#si existen eventos de mouse o teclado
glutMainLoop()

# End of program

#4.10.-
#glutWireSphere( a, b, c)
#el parametro a indica su relacion con la ventana por ejemplo si es 1 abarcara toda la ventana y si es 0.5 estara en la mitad de la ventana pero siempre en el centro de la ventana
#el parametro b indica cuantos meridianos tendra la esfera
#el parametro c indica cuantos paralelos tendra la esfera


