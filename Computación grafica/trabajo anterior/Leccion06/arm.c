#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

static int shoulder = 0, elbow = 0, munecax = 0,munecaz = 0,dedo1=0,dedo2=0,dedo3=0,dedo4=0,dedo5=0,falange1=0,falange2=0,falange3=0,falange4=0,falange5=0;

void init(void) 
{
  glClearColor (0.0, 0.0, 0.0, 0.0);
  glShadeModel (GL_FLAT);
}

void display(void)
{
   //brazo
   glClear (GL_COLOR_BUFFER_BIT);
   glPushMatrix();
   glTranslatef (-4.0, 0.0, 0.0);
   glRotatef ((GLfloat) shoulder, 0.0, 0.0, 1.0);
   glTranslatef (1.0, 0.0, 0.0);
   glPushMatrix();
   glScalef (2.0, 0.4, 1.0);
   glutWireCube (1.0);
   glPopMatrix();
   
   //antebrazo
   glTranslatef (1.0, 0.0, 0.0);
   glRotatef ((GLfloat) elbow, 0.0, 0.0, 1.0);
   glTranslatef (1.0, 0.0, 0.0);
   glPushMatrix();
   glScalef (2.0, 0.4, 1.0);
   glutWireCube (1.0);
   glPopMatrix();
   
   //mano
   glTranslatef (1.0, 0.0, 0.0);
   glRotatef ((GLfloat) munecaz, 0.0, 0.0, 1.0);
   glRotatef ((GLfloat) munecax, 1.0, 0.0, 0.0);
   glTranslatef (0.5, 0.0, 0.0);
   glPushMatrix();
   glScalef (1.0, 0.4, 1.0);
   glutWireCube (1.0);
   glPopMatrix();
   
   //dedo 1
   glPushMatrix();
   glTranslatef (0.0, 0.0, -0.5);//punto de apoyo
   glRotatef((GLfloat) dedo1, 1.0, 0.0, 0.0);
   glTranslatef (0.0, 0.0, -0.25);//ubicacion central del dedo1 en x , ubicacion dedo1 en el eje z
   glPushMatrix();
   glScalef (0.20, 0.40, 0.5 );
   glutWireCube (1.0);
   glPopMatrix();
   
   glPushMatrix();
   glTranslatef (0.0, 0.0, -0.125);//punto de apoyo
   glRotatef((GLfloat) falange2, 1.0, 0.0, 0.0);
   glTranslatef (0.0, 0.0, -0.125);//ubicacion central del falange en x , ubicacion falange en el eje z
   glScalef (0.20, 0.40, 0.25);
   glutWireCube (1.0);
   glPopMatrix();
   
   
   
   glPopMatrix();
   
   //dedo 2
   glPushMatrix();
   glTranslatef (0.5, 0.0, 0.0);//punto de apoyo
   glRotatef((GLfloat) dedo2, 0.0, 0.0, 1.0);
   glTranslatef (0.25, 0.0, 0.40);//ubicacion central del dedo2 en x , ubicacion dedo2 en el eje z
   glPushMatrix();
   glScalef (0.5, 0.40, 0.20);
   glutWireCube (1.0);
   glPopMatrix();	
   
   glPushMatrix();
   glTranslatef (0.25, 0.0, 0.0);//punto de apoyo
   glRotatef((GLfloat) falange2, 0.0, 0.0, 1.0);
   glTranslatef (0.25, 0.0, 0.0);//ubicacion central del falange en x , ubicacion falange en el eje z
   glScalef (0.5, 0.40, 0.20);
   glutWireCube (1.0);
   glPopMatrix();
   
   
   glPopMatrix();
   
   
   
   
   
   
   //dedo 3
   glPushMatrix();
   glTranslatef (0.5, 0.0, 0.0);//punto de apoyo
   glRotatef((GLfloat) dedo3, 0.0, 0.0, 1.0);
   glTranslatef (0.25, 0.0, 0.1333333);//ubicacion central del dedo3 en x, ubicacion dedo3 en el eje z
   glPushMatrix();
   glScalef (0.5, 0.40, 0.20);
   glutWireCube (1.0);
   glPopMatrix();	
   
   glPushMatrix();
   glTranslatef (0.25, 0.0, 0.0);//punto de apoyo
   glRotatef((GLfloat) falange3, 0.0, 0.0, 1.0);
   glTranslatef (0.25, 0.0, 0.0);//ubicacion central del falange en x , ubicacion falange en el eje z
   glScalef (0.5, 0.40, 0.20);
   glutWireCube (1.0);
   glPopMatrix();
   
   
   
   glPopMatrix();
   
   //dedo 4
   glPushMatrix();
   glTranslatef (0.5, 0.0, 0.0);//punto de apoyo
   glRotatef((GLfloat) dedo4, 0.0, 0.0, 1.0);
   glTranslatef (0.25, 0.0, -0.1333333);//ubicacion central del dedo4 en x, ubicacion dedo4 en el eje z
   glPushMatrix();
   glScalef (0.5, 0.40, 0.20);
   glutWireCube (1.0);
   glPopMatrix();
   
   glPushMatrix();
   glTranslatef (0.25, 0.0, 0.0);//punto de apoyo
   glRotatef((GLfloat) falange3, 0.0, 0.0, 1.0);
   glTranslatef (0.25, 0.0, 0.0);//ubicacion central del falange en x , ubicacion falange en el eje z
   glScalef (0.5, 0.40, 0.20);
   glutWireCube (1.0);
   glPopMatrix();
   
   
   
   glPopMatrix();
   
   //dedo 5
   glPushMatrix();
   glTranslatef (0.5, 0.0, 0.0);//punto de apoyo
   glRotatef((GLfloat) dedo5, 0.0, 0.0, 1.0);
   glTranslatef (0.25, 0.0, -0.40);//ubicacion central del dedo5 en x, ubicacion dedo5 en el eje z
   glPushMatrix();
   glScalef (0.5, 0.40, 0.20);
   glutWireCube (1.0);
   glPopMatrix();
   
   
   glPushMatrix();
   glTranslatef (0.25, 0.0, 0.0);//punto de apoyo
   glRotatef((GLfloat) falange3, 0.0, 0.0, 1.0);
   glTranslatef (0.25, 0.0, 0.0);//ubicacion central del falange en x , ubicacion falange en el eje z
   glScalef (0.5, 0.40, 0.20);
   glutWireCube (1.0);
   glPopMatrix();
   
   glPopMatrix();
   
   
   
   
   
   
   glPopMatrix();
   
   glPopMatrix();
   glutSwapBuffers();
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluPerspective(65.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef (0.0, 0.0, -5.0);
}

void keyboard (unsigned char key, int x, int y)
{
   switch (key) {
      case 's':   /*  s key rotates at shoulder  */
         shoulder = (shoulder + 5) % 360;
         glutPostRedisplay();
         break;
      case 'S':
         shoulder = (shoulder - 5) % 360;
         glutPostRedisplay();
         break;
      case 'e':  /*  e key rotates at elbow  */
         elbow = (elbow + 5) % 360;
         glutPostRedisplay();
         break;
      case 'E':
         elbow = (elbow - 5) % 360;
         glutPostRedisplay();
         break;
      case 'd':
         munecaz = (munecaz + 5) % 360;
         glutPostRedisplay();
         break;
      case 'D':
         munecaz = (munecaz - 5) % 360;
         glutPostRedisplay();
         break;
      case 'f':
         munecax = (munecax + 5) % 360;
         glutPostRedisplay();
         break;
      case 'F':
         munecax = (munecax - 5) % 360;
         glutPostRedisplay();
         break;
      case '1':
         dedo1 = (dedo1 - 5) % 360;
         glutPostRedisplay();
         break;
      case '!':
         dedo1 = (dedo1 + 5) % 360;
         glutPostRedisplay();
         break;
      case '2':
         dedo2 = (dedo2 - 5) % 360;
         glutPostRedisplay();
         break;
      case '"':
         dedo2 = (dedo2 + 5) % 360;
         glutPostRedisplay();
         break;
      case '3':
         dedo3 = (dedo3 - 5) % 360;
         glutPostRedisplay();
         break;
      case '#':
         dedo3 = (dedo3 + 5) % 360;
         glutPostRedisplay();
         break;
      case '4':
         dedo4 = (dedo4 - 5) % 360;
         glutPostRedisplay();
         break;
      case '$':
         dedo4 = (dedo4 + 5) % 360;
         glutPostRedisplay();
         break;
      case '5':
         dedo5 = (dedo5 - 5) % 360;
         glutPostRedisplay();
         break;
      case '%':
         dedo5 = (dedo5 + 5) % 360;
         glutPostRedisplay();
         break;
      case 'q':
         exit(0);
      default:
         break;
   }
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (1000, 600); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
   init ();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;
}
