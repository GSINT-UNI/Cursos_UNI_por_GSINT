
from OpenGL.GLUT import *
from OpenGL.GL import *
from OpenGL.GLU import *
#provee las herramientas para el manejo de graficas
import sys

#def - indica el inicio de un nuevo bloque de codigo
def draw():
    
    
  
	glClearColor(1.0,1.0,1.0,1.0)
	glClear(GL_COLOR_BUFFER_BIT)
	glPointSize(30);
	glBegin(GL_POINTS) 
	glColor3f(1.0,1.2,0.0)
	glVertex2f(-0.25,-0.25)
	glColor3f(0.0,1.0,0.2)
	glVertex2f(0.45,0.25)
	glColor3f(0.0,1.0,1.0)
	glVertex2f(-0.45,0.25)
	glColor3f(0.2,0.5,0.5)
	glVertex2f(0.25,-0.25) 
	glColor3f(0.6,1.0,0.0)
	glVertex2f(0.0,0.50)  
 
	glEnd()
 
 
	glColor3f(0.3,0.2,0.4) 
	glBegin(GL_LINES)   	
	glVertex2f(-0.25,-0.25)
	glVertex2f(0.25,-0.25)
	glVertex2f(0.25,-0.25)
	glVertex2f(0.45,0.25)
 	glVertex2f(0.45,0.25)
	glVertex2f(0.0,0.50)
	glVertex2f(0.0,0.50)
	glVertex2f(-0.45,0.25)   
	glVertex2f(-0.45,0.25)
	glVertex2f(-0.25,-0.25)   
	glEnd()
 
	glFlush() # Presenta el dibujo en la pantalla

def main():
	#sys.argv - permite ingresar parametros por consola, 
	# si fuera necesario
	glutInit(sys.argv) 

	#Utilizaremos un solo buffer de display - SINGLE
	# Y Utilizaremos el esquema de color RGB 
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA)
	glutInitWindowPosition(0,0)
	glutInitWindowSize(500, 500)
	glutCreateWindow("Mi primer Programa OPENGL")
	#indicamos a GLUT donde encontramos la funcion
	#que crea la escena Grafica en este caso - draw
	glutDisplayFunc(draw)
	
	
	#la siguiente funcion permite correr el programa 
	#en un loop continuo. Permite a GLUT chequear
	#si existen eventos de mouse o teclado
	glutMainLoop()
	return 0
main()
