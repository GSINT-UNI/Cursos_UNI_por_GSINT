#ejemplo3.py
#Crear un sistema de coordenadas con un punto de origen
from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *
import sys
#La siguiente es una funcion de inicializacion
def init():
	#utilizaremos el color negro como fondo
	#los numeros (de 0 a 1.0) corresponden a (Red,Green,Blue,alpha)
	glClearColor(0,0.5, 0.8, 1.0)
	#Definimos los rangos del sistema de coordenadas
	#gluOrtho2D(x-izquierda, x-derecha, y-abajo, y-arriba)
	# lo que coloca el origen (0,0) en el centro de la pantalla
	gluOrtho2D(-1.0, 1.0, -1.0, 1.0)
	#La siguiente funcion presenta la escena
def plotpoints():
	#la siguiente funcion limpia la pantalla y pinta el fondo
	#definido en init
	glClear(GL_COLOR_BUFFER_BIT)
	#Definimos el color de ploteo a rojo - 3f indica usar 3 parametros
	#tipo punto flotante de 0.0 a 1.0
	glColor3f(1.0, 1.0, 1.0)
	#Informamos al sistema de graficos que vamos a dibujar puntos
	glPointSize(2.0)
	glLineWidth(3.0)
	
	#puntos de la pregunta 4.15
	glBegin(GL_POINTS)
	glVertex2f(0.84, 0.59)
	glVertex2f(0.3, 0.0)
	glColor3f(1.0,0.0,0.0)
	glVertex2f(0.9, -0.4)
	glVertex2f(-0.7,0.1)
	glColor3f(1.0, 1.0,0.0)
	glVertex2f(0.2,-0.7)
	glVertex2f(-0.9,-0.1)
	glColor3f(0.0,1.0,0.0)
	glVertex2f(-0.12,-0.45)
	glVertex2f(-0.65,0.48)
	glColor3f(0.0,0.5,1.0)
	glVertex2f(-0.16,-0.72)
	glVertex2f(0.32,-0.21)
	glEnd()

	#triangulo de la pregunta 4.17
	glColor3f(0.0, 1.0, 0.0)
	glBegin(GL_LINES)
	glVertex2f(0.0,0.0)
	glVertex2f(0.8,0.0)
	glVertex2f(0.8,0.0)
	glVertex2f(0.4,0.5)
	glVertex2f(0.4,0.5)
	glVertex2f(0.0,0.0)
	glEnd()
	
	#resultado de la pregunta 4.18
	glBegin(GL_LINE_STRIP)
	glVertex2f(0.0, 0.0)
	glVertex2f(1.0,1.0)
	glVertex2f(-1.0,0.0)
	glEnd()
	
	#resultado de la pregunta 4.19
	glBegin(GL_LINE_LOOP)
	glVertex2f(0.0, 0.0)
	glVertex2f(1.0,1.0)
	glVertex2f(-1.0,0.0)
	glEnd()

	#ejes coordenados
	glBegin(GL_LINES)
	glColor3f(0.0, 0.0, 0.0)
	glVertex2f(-1, 0.0)
	glVertex2f(1, 0.0)
	glVertex2f(0.0,-1)
	glVertex2f(0.0,1)
	glEnd()
	
	#puntos simetricos al eje x
	glBegin(GL_POINTS)
	glColor3f(1.0, 0.0, 0.0)
	glVertex2f(-0.45,0.9)
	glVertex2f(-0.45,-0.9)
	
	#puntos simetricos a la recta x = y
	glColor3f(.0, 1.0, 1.0)
	glVertex2f(0.6,0.1)
	glVertex2f(0.1,0.6)
	glEnd()
	
	#trinagulos simetricos al eje y
	glBegin(GL_LINE_LOOP)
	glColor3f(0.0, 0.0, 1.0)
	glVertex2f(-0.8, -0.1)
	glVertex2f(-0.2, -0.1)
	glVertex2f(-0.5, -0.6)
	glEnd()
	
	glBegin(GL_LINE_LOOP)
	glVertex2f(0.8, -0.1)
	glVertex2f(0.2, -0.1)
	glVertex2f(0.5, -0.6)
	
	#Levantamos el lapiz - dejamos de dibujar
	glEnd()
	#presentamos la escena en pantalla
	glFlush()
#usaremos la funcion main para iniciar OPENGL y llamar
#rutinas de inicializacion como init
def main():
	glutInit(sys.argv)
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB)
	glutInitWindowSize(500,500)
	glutInitWindowPosition(50,50)
	glutCreateWindow("Dibujar Puntos")
	glutDisplayFunc(plotpoints)
	init()
	glutMainLoop()

main()
# End of Program
