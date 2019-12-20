# lab02-2.py
# Dibujando con OpenGL Parte 1
from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *
import sys
from time import sleep
# La siguiente es una funcion de inicializacion
global spin 

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
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(0.0, 0.3, 0.0)
    glPushMatrix()
    glTranslatef(0.0, 0.0,0.0)
    glutWireSphere(1.0, 15,15)
    glTranslatef(0.55,-0.65,-0.6)
    glColor3f(0.3, 0.6, 0.3)
    glutWireSphere(0.4, 15,15)

    glTranslatef(-1.1,0.0,0.0)
    glutWireSphere(0.4, 15,15)

    glTranslatef(-0.1,1.1,0.0)
    glutWireSphere(0.4, 15,15)

    glTranslatef(1.2,0.0,0.0)
    glutWireSphere(0.4, 15,15)

    glTranslatef(-0.6,0.6,0.6)
    glutWireSphere(0.45, 15,15)

    glPopMatrix()
    glutSwapBuffers();
    # Levantamos el lapiz - dejamos de dibujar
    # glEnd()
    # presentamos la escena en pantalla
    glFlush()
#La funcion reshape se llama cada vez que se redimensiona la ventana
#Los parametros que recibe son el ancho y la altura de la ventana
def reshape(width, height):
    #glViewport Define la porcion de ventana donde OpenGL podra dibujar
    #Parametros: DIst Horiz, Dist vert del inicio (Esq.Sup.Izquierda),
    #ancho y altura de la ventana
    glViewport(0, 0, min(width, height), min(width, height) );
    #glMatrixMode Define la matriz de transformacion elegida
    #Existen:GL_PROJECTION - proyeccion ,GL_MODELVIEW - Modelado,
    # GL_TEXTURE -Texturas2
    glMatrixMode(GL_PROJECTION);
    #glLoadIdentity carga como matriz de proyeccion la matriz identidad - la inicializa
    glLoadIdentity();
    #gluPerspective opera sobre la matriz de proyeccion y
    #define el angulo del campo de vision en sentido vertical (en grados)
    #la relacion entre la altura y la anchura de la figura (aspecto)
    #los planos: el mas cercano y el mas distante a la camara
    gluPerspective(60.0, 1, 1.0, 128.0);
    # Para las siguientes operaciones se elige la matriz de Modelado
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity()
    #gluLookAt define la transformacion sobre la vista inicial.
    #tiene 9 parametros: los primeros tres representan la
    #distancia en x, y, z de los ojos del observador
    #los siguientes tres, las coordenadas x,y, z del punto de referencia a observar
    # y los ultimos tres, la direccion del upVector
    gluLookAt(0.0, 2.0, 3.0, 0.0, 0.5, 0.5, 0.0, 1.0, 0.0);
# usaremos la funcion main para iniciar OPENGL y llamar
# rutinas de inicializacion como init
def keyboard(key, x, y):
    print key
    if (key == 'h'):
        print("help")
        print("c - switch culling")
        print("q/escape - Salir")
        print("1/2 - rotar")
    elif (key == 'c'):
        if (glIsEnabled(GL_CULL_FACE)):
            glDisable(GL_CULL_FACE)
            # print 'was enabled'
        else:
            glEnable(GL_CULL_FACE)
            # print 'was disabled'
    elif (key == '1'):
        glRotatef(1.0, 1., 0., 0.)
    elif (key == '2'):
        glRotatef(1.0, 0., 1., 0.)
    elif (key == 'q' or key == chr(27)):
        exit(0)
    # Esta funcion indica a la GLUT que es necesario redibujar la ventana
    glutPostRedisplay()

def mousefunction(button, state, x, y):
   spin = 0
   if (button == GLUT_LEFT_BUTTON and state == GLUT_DOWN ):
       spin = (spin + 30.0) % 360
       glRotate(15,spin,0.0,0.0)
       glutPostRedisplay()  
       

def main():
    glutInit(sys.argv)
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB)
    glutInitWindowSize(500, 500)
    glutInitWindowPosition(50, 50)
    glutCreateWindow("Laboratorio 2")
    glutDisplayFunc(display)
    init()
    glutReshapeFunc(reshape)
    glutKeyboardFunc(keyboard)    
    glutMouseFunc(mousefunction)
    glutMainLoop()
main()
# End of Program
