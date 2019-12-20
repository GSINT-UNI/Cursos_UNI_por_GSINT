# lab02-1.py
# Dibujando con OpenGL Parte 1

from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *
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


# La siguiente funcion presenta la escena
def display():
    # la siguiente funcion limpia la pantalla y pinta el fondo
    #glClearColor(1.0, 1.0, 1.0, 0.0);
    global x,y,z,vx,vz
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 1.0, 1.0, 128.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity()
    gluLookAt(1+x,1+y,1+z, 0.0+vx, 0.0, 0.0+vz, 0.0, 0.0, 1.0);
    glutPostRedisplay()
    
    print ("%d %d %d",x,y,z)
    
    
    glColor3f(1.0, 0.0, 0.0);

    glutWireTorus(0.15, 0.55, 28, 28);
    glColor3f(0.0, 0.0, 1.0);
    glutWireSphere(.50,28,28);
    
    
    glPushMatrix()
    glTranslatef(0.45, 0,0)
    glColor3f(0.0, 1.0, 0.0);
    glutWireSphere(.2,28,28);
    glPopMatrix()
    
    glPushMatrix()
    glTranslatef(0, 0.45,0)
    glColor3f(1.0, 1.0, 0.0);
    glutWireSphere(.2,28,28);
    glPopMatrix()
    
    glPushMatrix()
    glTranslatef(0, 0,0.45)
    glColor3f(0.0, 1.0, 1.0);
    glutWireSphere(.2,28,28);
    glPopMatrix()

    #glutWireCube(.60);
    glutSwapBuffers();

    # presentamos la escena en pantalla
    glFlush()

#La funcion reshape se llama cada vez que se redimensiona la ventana
#Los parametros que recibe son el ancho y la altura de la ventana
def reshape(width, height):
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
    gluPerspective(60.0, height / width, 1.0, 128.0);
    # Para las siguientes operaciones se elige la matriz de Modelado
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity()
    #gluLookAt define la transformacion sobre la vista inicial.
    #tiene 9 parametros: los primeros tres representan la
    #distancia en x, y, z de los ojos del observador
    #los siguientes tres, las coordenadas x,y, z del punto de referencia a observar
    # y los ultimos tres, la direccion del upVector
    gluLookAt(x,y,z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);


def keyPressed(*args):
	global x,y,z,vx,vz
	if args[0] == 'q':
		sys.exit()
	if args[0] == 'a':
		x-=0.1
	if args[0] == 'w':
		y+=0.1
	if args[0] == 's':
		y-=0.1
	if args[0] == 'd':
		x+=0.1
	if args[0] == 'u':
		z+=0.5
	if args[0] == 'i':
		z-=0.5
	if args[0] == '4':
		vx-=0.1
	if args[0] == '8':
		vz+=0.1
	if args[0] == '5':
		vz-=0.1
	if args[0] == '6':
		vx+=0.1

vx=0
vz=0
x=0
y=0
z=0

# usaremos la funcion main para iniciar OPENGL y llamar
# rutinas de	inicializacion como init
def main():
    glutInit(sys.argv)
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB)
    glutInitWindowSize(500, 500)
    glutInitWindowPosition(50, 50)
    glutCreateWindow("Laboratorio 2")
    init()	
    glutDisplayFunc(display)
    glutKeyboardFunc(keyPressed)
    glutReshapeFunc(reshape)
    glutMainLoop()


main()
# End of Program
