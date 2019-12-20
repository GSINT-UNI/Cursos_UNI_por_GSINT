# lab02-1.py
# Dibujando con OpenGL Parte 1

from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *
from math import sin,cos,sqrt,pi
import sys

# La siguiente es una funcion de inicializacion
def init():
    # utilizaremos el color negro como fondo
    # los numeros (de 0 a 1.0) corresponden a (Red,Green,Blue,alpha)
    glClearColor(0.0, 0.0, 0.0, 1.0)
    # Definimos los rangos del sistema de coordenadas
    # gluOrtho2D(x-izquierda, x-derecha, y-abajo, y-arriba)
    # lo que coloca el origen (0,0) en el centro de la pantalla
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0)


def Square(a,b,c):
	glBegin(GL_POLYGON)
	glVertex3f(0.0,0.0,0.0)
	glVertex3f(a,0.0,0.0)
	glVertex3f(a,b,0.0)
	glVertex3f(0,b,0.0)
	glEnd()

	glBegin(GL_POLYGON)
	glVertex3f(0.0,0.0,0.0)
	glVertex3f(a,0.0,0.0)
	glVertex3f(a,0.0,c)
	glVertex3f(0.0,0.0,c)
	glEnd()

	glBegin(GL_POLYGON)
	glVertex3f(a,b,0.0)
	glVertex3f(a,b,c)
	glVertex3f(a,0.0,c)
	glVertex3f(a,0.0,0.0)
	glEnd()

	glBegin(GL_POLYGON)
	glVertex3f(0.0,b,0.0)
	glVertex3f(a,b,0.0)
	glVertex3f(a,b,c)
	glVertex3f(0.0,b,c)
	glEnd()

	glBegin(GL_POLYGON)
	glVertex3f(0.0,b,c)
	glVertex3f(0.0,0.0,c)
	glVertex3f(0.0,0.0,0.0)
	glVertex3f(0.0,b,0.0)
	glEnd()

	glBegin(GL_POLYGON)
	glVertex3f(0.0,0.0,c)
	glVertex3f(a,0.0,c)
	glVertex3f(a,b,c)
	glVertex3f(0.0,b,c)
	glEnd()

	glColor3f(0,0,0)
	glBegin(GL_LINE_STRIP)
	glVertex3f(0.0,0.0,0.0)
	glVertex3f(a,0.0,0.0)
	glVertex3f(a,b,0.0)
	glVertex3f(0,b,0.0)
	glVertex3f(0.0,0.0,0.0)
	glEnd()

	glBegin(GL_LINES)
	glVertex3f(0.0,0.0,0.0)
	glVertex3f(0.0,0.0,c)
	glVertex3f(a,0.0,0.0)
	glVertex3f(a,0.0,c)
	glVertex3f(a,b,0.0)
	glVertex3f(a,b,c)
	glVertex3f(0,b,0.0)
	glVertex3f(0,b,c)
	glEnd()


	glBegin(GL_LINE_STRIP)
	glVertex3f(0.0,0.0,c)
	glVertex3f(a,0.0,c)
	glVertex3f(a,b,c)
	glVertex3f(0.0,b,c)
	glVertex3f(0.0,0.0,c)
	glEnd()


# La siguiente funcion presenta la escena
def display():
    # la siguiente funcion limpia la pantalla y pinta el fondo
    #glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    a= .8
    b=.8
    c=.8

    glBegin(GL_POLYGON)
    glVertex3f(0.0,0.0,0.0)
    glVertex3f(2,0.0,0.0)
    glVertex3f(3,4,0.0)
    glVertex3f(0,5,0.0)
    glEnd()
        
    
    
    #glutWireCube(.60);
    glutSwapBuffers();

    # presentamos la escena en pantalla
    glFlush()

#La funcion reshape se llama cada vez que se redimensiona la ventana
#Los parametros que recibe son el ancho y la altura de la ventana


def reshape(width, height):
    global y
    # glViewport Define la porcion de ventana donde OpenGL podra dibujar
    #Parametros: DIst Horiz, Dist vert del inicio (Esq.Sup.Izquierda),
    #ancho y altura de la ventana
    glViewport(0, 0, width, height);
    #glMatrixMode Define la matriz de transformacion elegida
    #Existen:GL_PROJECTION - proyeccion ,GL_MODELVIEW - Modelado,
    # GL_TEXTURE -Texturas
    glMatrixMode(GL_PROJECTION);
    #glLoadIdentity carga como matriz de proyeccion la matriz identidad - la inicializa
    glLoadIdentity();
    #gluPerspective opera sobre la matriz de proyeccion y
    #define el angulo del campo de vision en sentido vertical (en grados)
    #la relacion entre la altura y la anchura de la figura (aspecto)
    #los planos: el mas cercano y el mas distante a la camara
    gluPerspective(60.0, height / width, 2, 180.0);
    # Para las siguientes operaciones se elige la matriz de Modelado
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity()
    #gluLookAt define la transformacion sobre la vista inicial.
    #tiene 9 parametros: los primeros tres representan la
    #distancia en x, y, z de los ojos del observador
    #los siguientes tres, las coordenadas x,y, z del punto de referencia a observar
    # y los ultimos tres, la direccion del upVector
    

# usaremos la funcion main para iniciar OPENGL y llamar
# rutinas de	inicializacion como init
def main():
    glutInit(sys.argv)
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB)
    glutInitWindowSize(500, 500)
    glutInitWindowPosition(50, 50)
    glutCreateWindow("Laboratorio 2")
    glutDisplayFunc(display)
    init()
    glutKeyboardFunc(keyPressed)
    glutReshapeFunc(reshape)
    glutMainLoop()


main()
# End of Progra
