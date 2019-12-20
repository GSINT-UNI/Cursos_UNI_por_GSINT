/* Curvas bezier */
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

int plus = 0.0, minus = 0.0;


void petalo(void){
   GLfloat ptosctl [4][3] = { { 0.0,0.0,0.0},{9.0,9.0,0.0}, {8.0,-6.0,0.0}, {0.0,0.0,0.0} };
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glMap1f(GL_MAP1_VERTEX_3, 0, 1, 3, 4, &ptosctl[0][0]);
   glEnable(GL_MAP1_VERTEX_3);
   int i;   
   //curva de Bezier
   glLineWidth(4);
   glColor3f(0.0,0.5,0.0);
   glMapGrid1f(30,0,1);
   glEvalMesh1(GL_LINE,0,30);
   //Puntos de control
   glPointSize(6.0);
   glColor3f(1.0,1.0,1.0);
   glBegin(GL_POINTS);
   for(i=0; i<4; i++)
	glVertex3fv(&ptosctl[i][0]);
   glEnd();   
   glDisable(GL_MAP1_VERTEX_3);
}
void tallo(void){
   GLfloat ptosctl [4][3] = { { 0.0,0.0,0.0},{6.0,-5.0,0.0}, {6.0,-5.0,0.0}, {4.0,-10.0,0.0} };
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glMap1f(GL_MAP1_VERTEX_3, 0, 1, 3, 4, &ptosctl[0][0]);
   glEnable(GL_MAP1_VERTEX_3);
   int i;   
   //curva de Bezier
   glLineWidth(4);
   glColor3f(0.0,0.5,0.0);
   glMapGrid1f(30,0,1);
   glEvalMesh1(GL_LINE,0,30);
   //Puntos de control
   glPointSize(6.0);
   glColor3f(1.0,1.0,1.0);
   glBegin(GL_POINTS);
   for(i=0; i<4; i++)
	glVertex3fv(&ptosctl[i][0]);
   glEnd();   
   glDisable(GL_MAP1_VERTEX_3);

}

void display(void)
{   
   glClear (GL_COLOR_BUFFER_BIT);
   glRotatef(-15,0.0,0.0,1.0);
   glPushMatrix();
   petalo();
   glRotatef(90,0.0,0.0,1.0);
   petalo();
   glRotatef(90,0.0,0.0,1.0);
   petalo();
   glRotatef(90,0.0,0.0,1.0);
   petalo();
   glPopMatrix();
   tallo();
   glutSwapBuffers();
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   glOrtho(-10.0,10.0, -10.0,10.0,-10.0, 10.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

}

void special (int key, int x, int y)
{

  printf("%d\n", key);

}

/* ARGSUSED1 */
void keyboard (unsigned char key, int x, int y)
{
   printf("%d\n", key);
   switch (key) {
      case 's':
         //to do
         break;
      case 'm':
         //to do
         break;
      case 27:
         exit(0);
         break;
      default:
         break;
   }
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (800, 800); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("Curva de Bezier");
   //init ();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutKeyboardUpFunc(keyboard);
   glutSpecialUpFunc(special);
   glutMainLoop();
   return 0;
}
