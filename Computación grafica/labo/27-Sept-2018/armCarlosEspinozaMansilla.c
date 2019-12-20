#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>

static int shoulder = 0, elbow = 0, hand = 0, finger1 = 0, finger2 = 0, finger3 = 0, finger4 = 0, finger5 = 0;
double view_rotx, view_roty, view_rotz;

void init(void)
{
  glClearColor (0.0, 0.0, 0.0, 0.0);
  glShadeModel (GL_FLAT);
}

void display(void)
{
   glClear (GL_COLOR_BUFFER_BIT);
   
   
    glPushMatrix();
    glRotatef(view_rotx, 1.0, 0.0, 0.0);
    glRotatef(view_roty, 0.0, 1.0, 0.0);
    glRotatef(view_rotz, 0.0, 0.0, 1.0);
   
   
   
   glPushMatrix();
   glTranslatef (-1.0, 0.0, 0.0);
   glRotatef ((GLfloat) shoulder, 0.0, 0.0, 1.0);
   glTranslatef (1.0, 0.0, 0.0);
   glPushMatrix();
   glScalef (2.0, 0.4, 1.0);
   glutWireCube (1.0);
   glPopMatrix();

   glTranslatef (1.0, 0.0, 0.0);
   glRotatef ((GLfloat) elbow, 0.0, 0.0, 1.0);
   glTranslatef (1.0, 0.0, 0.0);
   glPushMatrix();
   glScalef (2.0, 0.4, 1.0);
   glutWireCube (1.0);
   glPopMatrix();
   
   /*creacion de mano*/ 
   glTranslatef (1.0, 0.0, 0.0);
   glRotatef ((GLfloat) hand, 0.0, 0.0, 1.0);
   glTranslatef (0.4, 0.0, 0.0);
   glPushMatrix();
   glScalef (1.0, 0.2, 1.0);
   glutWireCube (1.0);
   glPopMatrix();
   
   /*creacion de dedos*/
   /*----------1---------*/
   glPushMatrix();
   glTranslatef (0.54, 0.0, -0.45);
   glRotatef ((GLfloat) finger1, 0.0, 0.0, 1.0);
   glTranslatef (0.2, 0.0, 0.0);
   glPushMatrix();
   glScalef (0.5, 0.1, 0.1);
   glutWireCube (1.0);
   glPopMatrix();
   glTranslatef (0.3, 0.0, 0.0);
   glRotatef ((GLfloat) finger1, 0.0, 0.0, 1.0);
   glTranslatef (0.2, 0.0, 0.0);
   glPushMatrix();
   glScalef (0.5, 0.1, 0.1);
   glutWireCube (1.0);
   glPopMatrix();
   glPopMatrix();
   /*----------2---------*/
   glPushMatrix();
   glTranslatef (0.56, 0.0, -0.15);
   glRotatef ((GLfloat) finger2, 0.0, 0.0, 1.0);
   glTranslatef (0.2, 0.0, 0.0);
   glPushMatrix();
   glScalef (0.65, 0.1, 0.1);
   glutWireCube (1.0);
   glPopMatrix();
   glTranslatef (0.3, 0.0, 0.0);
   glRotatef ((GLfloat) finger2, 0.0, 0.0, 1.0);
   glTranslatef (0.2, 0.0, 0.0);
   glPushMatrix();
   glScalef (0.5, 0.1, 0.1);
   glutWireCube (1.0);
   glPopMatrix();
   glPopMatrix(); 
   /*----------3---------*/
   glPushMatrix();   
   glTranslatef (0.56, 0.0, 0.1);
   glRotatef ((GLfloat) finger3, 0.0, 0.0, 1.0);
   glTranslatef (0.2, 0.0, 0.0);
   glPushMatrix();
   glScalef (0.7, 0.1, 0.1);
   glutWireCube (1.0);
   glPopMatrix();
   glTranslatef (0.3, 0.0, 0.0);
   glRotatef ((GLfloat) finger3, 0.0, 0.0, 1.0);
   glTranslatef (0.2, 0.0, 0.0);
   glPushMatrix();
   glScalef (0.5, 0.1, 0.1);
   glutWireCube (1.0);
   glPopMatrix();
   glPopMatrix();   
   /*----------4---------*/
   glPushMatrix();      
   glTranslatef (0.56, 0.0, 0.35);
   glRotatef ((GLfloat) finger4, 0.0, 0.0, 1.0);
   glTranslatef (0.2, 0.0, 0.0);
   glPushMatrix();
   glScalef (0.6, 0.1, 0.1);
   glutWireCube (1.0);
   glPopMatrix();
   glTranslatef (0.3, 0.0, 0.0);
   glRotatef ((GLfloat) finger4, 0.0, 0.0, 1.0);
   glTranslatef (0.2, 0.0, 0.0);
   glPushMatrix();
   glScalef (0.5, 0.1, 0.1);
   glutWireCube (1.0);
   glPopMatrix();
   glPopMatrix();   
   /*----------5---------*/
   glPushMatrix();         
   glTranslatef (0.1, 0.07, 0.45);
   glRotatef ((GLfloat) finger5, 1.0, 0.0, 0.0);
   glTranslatef (0.0, 0.2, 0.0);
   glPushMatrix();
   glScalef (0.2, 0.5, 0.1);
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
      case 'f':  /*  f key rotates at hand  */
         hand = (hand + 5) % 360;
         glutPostRedisplay();
         break;
      case 'F':
         hand = (hand - 5) % 360;
         glutPostRedisplay();
         break;
      /*------------1-----------------------*/   
      case '1':  /*  1 key rotates at finger1  */
         finger1 = (finger1 + 5) % 360;
         glutPostRedisplay();
         break;
      case '2':
         finger1 = (finger1 - 5) % 360;
         glutPostRedisplay();
         break;
      /*------------2-----------------------*/   
      case '3':  /*  1 key rotates at finger2  */
         finger2 = (finger2 + 5) % 360;
         glutPostRedisplay();
         break;
      case '4':
         finger2 = (finger2 - 5) % 360;
         glutPostRedisplay();
         break;
      /*------------1-----------------------*/   
      case '5':  /*  1 key rotates at finger3  */
         finger3 = (finger3 + 5) % 360;
         glutPostRedisplay();
         break;
      case '6':
         finger3 = (finger3 - 5) % 360;
         glutPostRedisplay();
         break;
      /*------------1-----------------------*/   
      case '7':  /*  1 key rotates at finger4  */
         finger4 = (finger4 + 5) % 360;
         glutPostRedisplay();
         break;
      case '8':
         finger4 = (finger4 - 5) % 360;
         glutPostRedisplay();
         break;
      /*------------1-----------------------*/   
      case '9':  /*  1 key rotates at finger5  */
         finger5 = (finger5 - 5) % 360;
         glutPostRedisplay();
         break;
      case '0':
         finger5 = (finger5 + 5) % 360;
         glutPostRedisplay();
         break;
            
      default:
         break;
   }
}

void special(int key, int  x, int y){
    

    if ( key == GLUT_KEY_UP )
        view_rotx += 5.0;
    else if ( key == GLUT_KEY_DOWN )
        view_rotx -= 5.0;
    else if ( key == GLUT_KEY_LEFT )
        view_roty += 5.0;
    else if ( key == GLUT_KEY_RIGHT )
        view_roty -= 5.0;
    else
        return ;
    glutPostRedisplay();  
}


int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (800, 500);
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
   init ();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutSpecialFunc(special);
   printf("s,e,f,S,E,F: Para controlar el brazo\n1,2,3,4,5,6,7,8,9,0: Para controlar los dedos\nflechas: Para controlar la perspectiva\n\n");
   
   glutMainLoop();
   return 0;
}
