# lab02-1.py
# Dibujando con OpenGL Parte 1

from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *
from math import atan,sin,cos,pi
import sys

p0=[0,0,5];
m=0.3;
teta = 0;
a=[m*cos(teta*pi/180),m*sin(teta*pi/180)];
l=[m*sin(teta*pi/180),-1*m*cos(teta*pi/180)];
p1=[p0[0]+m*cos(teta),p0[1]+m*sin(teta),p0[2]];
salto=0;
conts=0;
# La siguiente es una funcion de inicializacion
def init():
    # utilizaremos el color negro como fondo
    # los numeros (de 0 a 1.0) corresponden a (Red,Green,Blue,alpha)
    glClearColor(0.0, 0.0, 0.0, 1.0)
    
    # Definimos los rangos del sistema de coordenadas
    # gluOrtho2D(x-izquierda, x-derecha, y-abajo, y-arriba)
    # lo que coloca el origen (0,0) en el centro de la pantalla
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0)

def camara():
	global p0,p1,m
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1.0, 0, 128.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity()
	gluLookAt(p0[0],p0[1],p0[2], p1[0], p1[1], p1[2], 0.0, 0.0, 1.0);
	glutPostRedisplay()


pb=[5,5,5,0,0]
a_b=[0,0,0]
vis_b = 0
def mov_bala():
	c=3
	global pb,a_b
	pb[0] = pb[0] +a_b[0]*c
	pb[1] = pb[1] +a_b[1]*c
	pb[2] = pb[2] +a_b[2]*c
	glutPostRedisplay()

def dibujar_bala(x,y,z,tet,alfa):
	glPushMatrix();
	glTranslatef(x,y,z)
	glRotatef(tet,0,0,1)
	glRotatef(alfa,0,-1,0)
	glScalef(0.01,0.01,0.01)
	k=0
	for i in range(0,720*5):
		k+=0.1
		glColor3f(1,0,0)
		#disco
		glBegin(GL_LINES)
		glVertex3f(0.3*sin(k*pi/180),0.3*cos(k*pi/180),0)
    		glVertex3f(0,cos(k*pi/180),sin(k*pi/180))
    		glEnd()
    		#cilindro
    		glBegin(GL_LINES)
		glVertex3f(0,cos(k*pi/180),sin(k*pi/180))
    		glVertex3f(2,cos(k*pi/180),sin(k*pi/180))
    		glEnd()
		#cono
		glBegin(GL_LINES)
		glVertex3f(2,cos(k*pi/180),sin(k*pi/180))
    		glVertex3f(3.5,0,0)
    		glEnd()	
	glPopMatrix();

def dibujar_piso(x,y,z):
	glPushMatrix();
	glTranslatef(x, y, z)
	glColor3f(0,0,1);
	glBegin(GL_QUADS)  # Start Drawing The Cube
  	# Front Face (note that the texture's corners have to match the quad's corners)
    	glVertex3f(-1.0, -1.0, 0)  # Bottom Left Of The Texture and Quad
    	glVertex3f(1.0, -1.0, 0)  # Bottom Right Of The Texture and Quad
    	glVertex3f(1.0, 1.0, 0)  # Top Right Of The Texture and Quad
    	glVertex3f(-1.0, 1.0, 0)  # Top Left Of The Texture and Quad
    	glEnd()
	glPopMatrix();


# La siguiente funcion presenta la escena
def display():
    glClearColor(1.0, 1.0, 1.0, 0.0);
    
    camara();
    global p1,p0,a,l,pb,vis_b
    d=1
    actualizar_estado()
    
    glPushMatrix()
    glTranslatef(-50,-50,0)#para ubicarte en el centro
    for i in range(0,100,3):
    	for j in range(0,100,3):
    		dibujar_piso(i,j,0);
    glPopMatrix()
    
    glPushMatrix()
    glTranslatef(-50,-50,0)#para ubicarte en el centro
    for i in range(0,100,3):
    	for j in range(0,100,3):
    		dibujar_piso(i,j,0);
    glPopMatrix()
    
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(1,1,1);
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
    glPopMatrix()
    
    
    if vis_b==1:
    	dibujar_bala(pb[0],pb[1],pb[2],pb[3],pb[4])
    	mov_bala()
    
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
    gluLookAt(p0[0],p0[1],p0[2], p1[0],p1[1],p1[2], 0.0, 0.0, 1.0);


def keyPressed(*args):
	global p0,p1,a,l,teta,m,salto,conts,pb,a_b,vis_b
	a=[m*cos(teta*pi/180),m*sin(teta*pi/180)];
	l=[m*sin(teta*pi/180),-1*m*cos(teta*pi/180)];
	
	if args[0] == 'q':
		sys.exit()
	if args[0] == 'a':
		p0[0]=p0[0]-l[0];
		p0[1]=p0[1]-l[1];
		p1[0]=p1[0]-l[0];
		p1[1]=p1[1]-l[1];
		
	if args[0] == 'w':
		p0[0]=p0[0]+a[0];
		p0[1]=p0[1]+a[1];
		p1[0]=p1[0]+a[0];
		p1[1]=p1[1]+a[1];

	if args[0] == 's':
		p0[0]=p0[0]-a[0];
		p0[1]=p0[1]-a[1];
		p1[0]=p1[0]-a[0];
		p1[1]=p1[1]-a[1];
	if args[0] == 'd':
		p0[0]=p0[0]+l[0];
		p0[1]=p0[1]+l[1];
		p1[0]=p1[0]+l[0];
		p1[1]=p1[1]+l[1];
	if args[0] == ' ' and salto==0:
		salto=1;
		conts=0;
	if args[0] == 'i':
		p0[2]-=0.1
		p1[2]-=0.1
	if args[0] == '8':
		p1[2]+=0.01
	if args[0] == '5':
		p1[2]-=0.01
	if args[0] == '6':
		teta-=2
		p1[0]=p0[0]+m*cos(teta*pi/180)
		p1[1]=p0[1]+m*sin(teta*pi/180)
	if args[0] == '4':
		teta+=2
		p1[0]=p0[0]+m*cos(teta*pi/180)
		p1[1]=p0[1]+m*sin(teta*pi/180)
	if args[0] == 'f' and vis_b == 0:
		vis_b = 1
		pb[0] = p0[0]+a[0]
		pb[1] = p0[1]+a[1]
		pb[2] = p1[2]
		pb[3] = teta
		pb[4] = atan((p1[2]-p0[2])/m)*180/pi
		#print repr(pb[4])
		a_b = [p1[0]-p0[0],p1[1]-p0[1],p1[2]-p0[2]]
	if args[0] == 'r':
		vis_b=0
	glutPostRedisplay()
		
def actualizar_estado():
	global salto, conts, p0,p1
	if salto==1:
		conts+=1
		if conts<10:
			p0[2]+=0.3
			p1[2]+=0.3
		elif conts>=10 and p0[2]>5:
			p0[2]-=0.3
			p1[2]-=0.3
		elif p0[2]<=5:
			p0[2]=5
			salto=0
		glutPostRedisplay()
	

# usaremos la funcion main para iniciar OPENGL y llamar
# rutinas de inicializacion como init
def main():
    glutInit(sys.argv)
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB)
    glutInitWindowSize(500, 500)
    glutInitWindowPosition(50, 50)
    glutCreateWindow("Chavin-de-Huantar")
    init()	
    glutDisplayFunc(display)
    glutKeyboardFunc(keyPressed)
    glutReshapeFunc(reshape)
    glutMainLoop()


main()
# End of Program
