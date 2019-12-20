// Very Simple OpenGL Evaluator Demo

#include <iostream>
#include <stdlib.h>

#include <GL/glut.h> // GLUT stuff - includes OpenGL headers

// For Bezier curve
const int numcontrolpts = 4;  // Number of control points
                              // Below are coord's of control points
                             // (Must use 3 coord's each, even in 2-D.)
GLfloat controlpts[numcontrolpts][3] = {
   {-0.9, -0.9,  0.0},
   {-0.5, -0.2,  0.0}, 
   {-0.2, -0.3,  0.0},
   { 0.0,  0.0,  0.0}
};

GLfloat controlpts2[numcontrolpts][3] = {
   {-0.0, -0.0,  0.0},
   { 0.1,  0.5,  0.0}, 
   { 0.2,  0.3,  0.0},
   { 0.9,  0.9,  0.0}
};

int numdrawsegs = 20;         // Number of segments drawn in the Bezier curve

const int startwinsize = 400; // Starting window width & height, in pixels


// The GLUT display function
void display()
{
   // Clear screen
   glClear(GL_COLOR_BUFFER_BIT);

   // Draw Bezier curve
   glColor3d(0.9, 0.1, 0.1);
   glLineWidth(3.0);

   //glEvalMesh1(GL_LINE, 0, numdrawsegs);

   // Here, We used an evaluator grid.
   // Code to do the same thing, "manually", is as follows:

   // Set up Bezier curve evaluator
   glMap1f(GL_MAP1_VERTEX_3,   // target: 1-d [curve], 3 coord's per pt
           0.0, 1.0,           // start & end param value
           3,                  // "stride": pts stored 3 GLfloat's apart
           numcontrolpts,      // no. of control points
           &controlpts[0][0]); // control pt data
   glEnable(GL_MAP1_VERTEX_3); // Enable this evaluator

   glBegin(GL_LINE_STRIP);
      for (int i=0; i<=numdrawsegs; ++i)
         glEvalCoord1d(GLdouble(i)/numdrawsegs);
   glEnd();



   glColor3d(0.1, 0.9, 0.1);
   glLineWidth(3.0);

   //glEvalMesh1(GL_LINE, 0, numdrawsegs);

   // Here, We used an evaluator grid.
   // Code to do the same thing, "manually", is as follows:

   // Set up Bezier curve evaluator
   glMap1f(GL_MAP1_VERTEX_3,   // target: 1-d [curve], 3 coord's per pt
           0.0, 1.0,           // start & end param value
           3,                  // "stride": pts stored 3 GLfloat's apart
           numcontrolpts,      // no. of control points
           &controlpts2[0][0]); // control pt data
   glEnable(GL_MAP1_VERTEX_3); // Enable this evaluator

   glBegin(GL_LINE_STRIP);
      for (int i=0; i<=numdrawsegs; ++i)
         glEvalCoord1d(GLdouble(i)/numdrawsegs);
   glEnd();

   glutSwapBuffers();
}


// The GLUT reshape function
void reshape(int w, int h)
{
   glViewport(0, 0, w, h);

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   // We set up coordinate system so that aspect ratios are always correct,
   //  and the region from -1..1 in x & y always just fits in the viewport.
   if (w > h)
   {
      gluOrtho2D(-double(w)/h, double(w)/h, -1., 1.);
   }
   else
   {
      gluOrtho2D( -1., 1., -double(h)/w, double(h)/w);
   }

   glMatrixMode(GL_MODELVIEW);  // Always go back to modelview mode
   glLoadIdentity();
}


// The GLUT keyboard function
void keyboard(unsigned char key, int x, int y)
{
   switch (key)
   {
   case 27:  // Escape Key -- good way to quit
      exit(0);  // Quit
      break;
   case 'x':
   case 'X':
		//controlpts[4][0]=controlpts[4][0]+0.1;
		//glutPostRedisplay();
		break;
		//dx4=dx4+0.1;
		//dz4=dz4+0.0;                              
   case 'y':
   case 'Y':
		//controlpts[4][1]=controlpts[4][1]+0.1;
		//glutPostRedisplay();
   		//dy4=dy4+0.1;
		//dz4+=0.0;                              
		break;
   }
}


// Initializes GL states
void init()
{
   // Set background color
   glClearColor(1.0, 1.0, 1.0, 0.0);

   

   // Set up grid for evaluator.
   // This only needs to be done when using glEvalMesh1.
   //glMapGrid1d(numdrawsegs, 0.0, 1.0);
}


int main(int argc, char ** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize(startwinsize, startwinsize);
   glutInitWindowPosition(50, 50);
   glutCreateWindow("CC322 - Simple OpenGL Evaluator Demo");

   init();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);


   glutMainLoop();

   return 0;
}
