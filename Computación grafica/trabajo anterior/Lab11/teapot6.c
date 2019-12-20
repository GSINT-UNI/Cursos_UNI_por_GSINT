/*
 * Draw simple OPENGL 2D primitives  point/line/triangle
 */

#include <GL/glut.h>


/* predefine function names */
void initgl();
void display(void);
void specialFunc (int key, int x, int y);
void Keyboard(unsigned char key, int x, int y);
void Reshape (int w, int h);

float rot = 0;




/* main program - setup window using GLUT */
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Color Teapot");
    glutDisplayFunc(display);
    initgl();
    glutKeyboardFunc(Keyboard);
    glutSpecialFunc(specialFunc);
    glutMainLoop();
    return  0;
}


float camara_pos[] = {0,0,0};

/* Initialisation of OpenGL */
static GLfloat light0_position [] = {1.0,1.0,1.0,0.0};
static GLfloat mat_specular [] = {0.0,1.0,0.0,1.0};
static GLfloat mat_shininess [] = {50.0};
static GLfloat mat_ambient [] = {0,0,1,1};
static GLfloat mat_diffuse [] = {0,1,0,1};
int sp=1;
int sh=1;

void initgl()
{
   glEnable (GL_DEPTH_TEST);

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-1.0, 1.0, -1.0, 1.0,0, 100.0);
   glMatrixMode(GL_MODELVIEW);

   glEnable (GL_LIGHTING);
   glEnable (GL_LIGHT0);

   glClearColor (1.0, 1.0, 1.0, 1.0);
   glColor3f(0.5,0.5,0.5);

   glMaterialfv (GL_FRONT, GL_DIFFUSE , mat_diffuse );
   glMaterialfv (GL_FRONT, GL_AMBIENT , mat_ambient );
   glMaterialfv (GL_FRONT, GL_SPECULAR, mat_specular );
   glMaterialfv (GL_FRONT, GL_SHININESS, mat_shininess );

   glColorMaterial (GL_FRONT, GL_DIFFUSE);
   glEnable (GL_COLOR_MATERIAL);
   glShadeModel(GL_SMOOTH);
}

/* display function called by OpenGL */
void display(void)
{
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    gluLookAt(camara_pos[0],camara_pos[1],camara_pos[2],0,0,-2,0,1,0);
    glPushMatrix();
    glTranslatef(0,0,-2);
    glRotatef(rot, 0.0, 1.0, 0.0);

    glColor3f(1.0,0.0,0.0);
    glutSolidTeapot(0.5);
    glPopMatrix();
    glPushMatrix();

    glLightfv (GL_LIGHT0, GL_POSITION, light0_position);
    glTranslatef(light0_position[0],light0_position[1],light0_position[2]);
    glDisable(GL_LIGHTING);
    glColor3f(0,0,1);
    glutWireCube(0.1);
    glEnable(GL_LIGHTING);
    glPopMatrix();

    glPopMatrix();
    glFlush();
}


void Reshape (int w, int h) {

    glViewport (0, 0, (GLsizei)w, (GLsizei)h); //set the viewport to the current window specifications
    glMatrixMode (GL_PROJECTION); //set the matrix to projection

    glLoadIdentity ();
    gluPerspective (60, (GLfloat)w / (GLfloat)h, 0 , 100.0); //set the perspective (angle of sight, width, height, ,depth)
    //glMatrixMode (GL_MODELVIEW); //set the matrix back to model
}

void Keyboard(unsigned char key, int x, int y){
   if (key==27)
      exit(0);
   if (key=='a')
      camara_pos[0]-=1;
   if (key=='w')
      camara_pos[2]-=1;
   if (key=='s')
      camara_pos[2]+=1;
   if (key=='d')
      camara_pos[0]+=1;
   if (key=='r')
      camara_pos[1]+=1;
   if (key=='f')
      camara_pos[1]-=1;
   if (key=='j')
      light0_position[0]-=0.1;
   if (key=='i')
      light0_position[1]+=0.1;
   if (key=='k')
      light0_position[1]-=0.1;
   if (key=='l')
      light0_position[0]+=0.1;
   if (key=='o')
      light0_position[2]-=0.1;
   if (key=='p')
      light0_position[2]+=0.1;
   if(key =='v')
      glDisable (GL_COLOR_MATERIAL);
   if(key=='b')
      glEnable (GL_COLOR_MATERIAL);
   display();
}

void specialFunc (int key, int x, int y){
   if (key == GLUT_KEY_LEFT)
      rot-=5;
   if (key== GLUT_KEY_RIGHT)
      rot+=5;
   display();
}
