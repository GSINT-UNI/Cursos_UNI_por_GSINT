/*
 * Draw simple OPENGL 2D primitives  point/line/triangle
 */

#include <GL/glut.h>
#include <math.h>
#include <iostream>

using namespace std;
/* predefine function names */
void initgl();
void display(void);
void specialFunc (int key, int x, int y);
void Keyboard(unsigned char key, int x, int y);
void Reshape (int w, int h);
void camara();
void dibujar_cubo(float x, float y, float z, float a,float b,float c);
void draw_lamp();
void draw_table();
/* main program - setup window using GLUT */
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("LabPC13");
    glutDisplayFunc(display);
    initgl();
    glutKeyboardFunc(Keyboard);
    glutSpecialFunc(specialFunc);
    glutMainLoop();
    return  0;
}

float camara_pos[] = {2,5,0};


void initgl()
{
   glEnable (GL_DEPTH_TEST);

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glMatrixMode(GL_MODELVIEW);
   glClearColor (0,0,0, 1.0);

}

void camara(){
   glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);

   glLoadIdentity();
   gluPerspective(60.0,1.0,0.1,100.0);
   glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(camara_pos[0],camara_pos[1],camara_pos[2],-0.5,0.5,-9,0,1,0);
   //cout << camara_pos[0]<<" " << camara_pos[1]<<" " << camara_pos[2]<<endl;
}

float rot=0;
void display(void)
{
   GLfloat mat_ambient[] = { 0.7,0.7,0.7,1.0f };
   GLfloat mat_diffuse[] = {0.5,0.5,0.5,1  };
   GLfloat mat_specular[] = { 1,1,1, 1.0f };
   GLfloat shine[] = {25};

   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glEnable(GL_COLOR_MATERIAL);

   camara();

//paredes
   glColor3f(0.5,0.3,0);
   dibujar_cubo(-3.5,-2,-12, 7,0.2,7);
   glColor3f(1,0.7,0);
   dibujar_cubo(-4,-2,-12, 0.5,7,7);
   dibujar_cubo(-4,-2,-12.5, 7.5,7,0.5);
   dibujar_cubo(3.5,-2,-12.5, 0.5,7,7.5);

   glPushMatrix();
   glRotatef(rot,0,1,0);
//mesa
   draw_table();

//tetera

   glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, shine);
   glColorMaterial (GL_FRONT, GL_DIFFUSE);
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glPushMatrix();
   glColor3f(0.5,0.5,0.5);
   glTranslatef(-0.5,0.5,-9);
   glutSolidTeapot(0.5);
   glPopMatrix();
   glDisable(GL_LIGHTING);
   glDisable(GL_LIGHT0);
   glPopMatrix();
//lampara
   glColor3f(0.2,0.2,0.2);
   dibujar_cubo(-2.5,-1.3,-6, 0.2,3,0.2);
   glColor3f(0.3,0.3,0.3);
   dibujar_cubo(-2.67,-1.8,-6.22, 0.5,0.5,0.5);
   glColor3f(0.3,0.3,0.3);

   glPushMatrix();
   glTranslatef(-2.4,1.9,-5.84);
   glColor3f(1,1,0);
   glutSolidSphere(0.2,15,15);
   draw_lamp();
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
   if (key=='v')
      rot++;
   if (key=='b')
      rot--;
/*   if (key=='j')
      light0_position[0]-=0.1;
   if (key=='l')
      light0_position[0]+=0.1;
   if (key=='k')
      light0_position[1]-=0.1;
   if (key=='i')
      light0_position[1]+=0.1;
   if (key=='o')
      light0_position[2]-=0.1;
   if (key=='p')
      light0_position[2]+=0.1;
*/
   display();
}

void specialFunc (int key, int x, int y){
   /*if (key == GLUT_KEY_LEFT)
      rot-=5;
   if (key== GLUT_KEY_RIGHT)
      rot+=5;
   */display();
}

void dibujar_cubo(float x, float y, float z, float a,float b,float c){
   glPushMatrix();
   glTranslatef(x,y,z);
   glBegin(GL_QUADS);
//cara de abajo
   glVertex3f(0,0,0);
   glVertex3f(0,0,c);
   glVertex3f(a,0,c);
   glVertex3f(a,0,0);
//cara de la izquierda
   glVertex3f(0,0,0);
   glVertex3f(a,0,0);
   glVertex3f(a,b,0);
   glVertex3f(0,b,0);
//cara de la derecha
   glVertex3f(0,0,c);
   glVertex3f(a,0,c);
   glVertex3f(a,b,c);
   glVertex3f(0,b,c);
//cara de adelante
   glVertex3f(0,0,0);
   glVertex3f(0,0,c);
   glVertex3f(0,b,c);
   glVertex3f(0,b,0);
//cara de atras
   glVertex3f(a,0,0);
   glVertex3f(a,0,c);
   glVertex3f(a,b,c);
   glVertex3f(a,b,0);
//cara de arriba
   glVertex3f(0,b,0);
   glVertex3f(0,b,c);
   glVertex3f(a,b,c);
   glVertex3f(a,b,0);

   glEnd();
   glPopMatrix();
}

void draw_lamp(){
   glPushMatrix();
   glTranslatef(0,-0.5,0);
   float teta=0;
   float r,R;
   r=0.3;
   R=0.5;
   glColor3f(0.9,0.2,0);
   glBegin(GL_QUADS);
   while(teta<360){
      glVertex3f(r*cos(teta*M_PI/180),  1,r*sin(teta*M_PI/180));
      glVertex3f(r*cos((teta+10)*M_PI/180),   1  ,r*sin(teta*M_PI/180));
      glVertex3f(R*cos(teta*M_PI/180),   0  ,R*sin(teta*M_PI/180));
      glVertex3f(R*cos((teta+10)*M_PI/180),  0 ,R*sin(teta*M_PI/180));
      teta+=0.01;
   }

   glEnd();
   glPopMatrix();
}

void draw_table(){
   glColor3f(0.4,0.2,0);
   dibujar_cubo(-1.5,-1.8,-10,0.2,2,0.2);
   dibujar_cubo(1,-1.8,-10,0.2,2,0.2);
   dibujar_cubo(1,-1.8,-8,0.2,2,0.2);
   dibujar_cubo(-1.5,-1.8,-8,0.2,2,0.2);
   dibujar_cubo(-1.6,0,-10, 3,0.2,3);
}
