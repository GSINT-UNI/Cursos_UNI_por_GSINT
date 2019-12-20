#include <GL/glut.h>

float posicion;
int grados;
float posx=0;

void reshape(int width, int height){
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-10, 10, -10, 10, 0.1f, 20);
  glTranslatef(-3.0f, 0.0f, -15.0f);
  glMatrixMode(GL_MODELVIEW);
}


void dibujar_rueda_y_tornillos_delante(){
  glPushMatrix();
  glColor3f(0.5f,0.5f,0.5f);  
  glTranslatef(1.5f,0.0f, 0.0f);
  glutSolidSphere(1.0f,20,20);
  
  float d=0.5;
  //tornillo1
  glPushMatrix();
  glColor3f(0.0f,0.0f,0.0f);
  glTranslatef(d,0.0f, 0.0f);
  glutSolidSphere(0.1f,20,20);
  glPopMatrix();
  
  //tornillo2
  glPushMatrix();
  glColor3f(0.0f,0.0f,0.0f);
  glTranslatef(0.5f*d,0.866054038f*d, 0.0f);
  glutSolidSphere(0.1f,20,20);
  glPopMatrix();
  
  //tornillo3
  glPushMatrix();
  glColor3f(0.0f,0.0f,0.0f);
  glTranslatef(-0.5f*d,0.866054038f*d, 0.0f);
  glutSolidSphere(0.1f,20,20);
  glPopMatrix();
  
  //tornillo4
  glPushMatrix();
  glColor3f(0.0f,0.0f,0.0f);
  glTranslatef(-d,0.0f, 0.0f);
  glutSolidSphere(0.1f,20,20);
  glPopMatrix();
  
  //tornillo5
  glPushMatrix();
  glColor3f(0.0f,0.0f,0.0f);
  glTranslatef(-0.5f*d,-0.866054038f*d, 0.0f);
  glutSolidSphere(0.1f,20,20);
  glPopMatrix();
  
  //tornillo6
  glPushMatrix();
  glColor3f(0.0f,0.0f,0.0f);
  glTranslatef(0.5f*d,-0.866054038f*d, 0.0f);
  glutSolidSphere(0.1f,20,20);
  glPopMatrix();
  
  glPopMatrix();
}

void dibujar_rueda_y_tornillos_detras(){
  glPushMatrix();
  glColor3f(0.5f,0.5f,0.5f);  
  glTranslatef(5.5f,0.0f, 3.0f);
  glutSolidSphere(1.0f,20,20);
  
  float d=0.5;
  //tornillo1
  glPushMatrix();
  glColor3f(0.0f,0.0f,0.0f);
  glTranslatef(d,0.0f, 0.0f);
  glutSolidSphere(0.1f,20,20);
  glPopMatrix();
  
  //tornillo2
  glPushMatrix();
  glColor3f(0.0f,0.0f,0.0f);
  glTranslatef(0.5f*d,0.866054038f*d, 0.0f);
  glutSolidSphere(0.1f,20,20);
  glPopMatrix();
  
  //tornillo3
  glPushMatrix();
  glColor3f(0.0f,0.0f,0.0f);
  glTranslatef(-0.5f*d,0.866054038f*d, 0.0f);
  glutSolidSphere(0.1f,20,20);
  glPopMatrix();
  
  //tornillo4
  glPushMatrix();
  glColor3f(0.0f,0.0f,0.0f);
  glTranslatef(-d,0.0f, 0.0f);
  glutSolidSphere(0.1f,20,20);
  glPopMatrix();
  
  //tornillo5
  glPushMatrix();
  glColor3f(0.0f,0.0f,0.0f);
  glTranslatef(-0.5f*d,-0.866054038f*d, 0.0f);
  glutSolidSphere(0.1f,20,20);
  glPopMatrix();
  
  //tornillo6
  glPushMatrix();
  glColor3f(0.0f,0.0f,0.0f);
  glTranslatef(0.5f*d,-0.866054038f*d, 0.0f);
  glutSolidSphere(0.1f,20,20);
  glPopMatrix();
  
  glPopMatrix();
}


void dibujar_ventanas(){
  glPushMatrix();
  glColor3f(0.0f,0.0f,1.0f);  
  glTranslatef(1.2f,1.8f, 0.01f);

  glBegin(GL_TRIANGLES);
      glVertex3f(0.0f, 0.0f, 0.0f);
      glVertex3f(0.8f, 0.0f, 0.0f); 
      glVertex3f(0.8f, 0.8f, 0.0f); 
  glEnd();

  glBegin(GL_QUADS);
      glVertex3f(0.8f, 0.0f, 0.0f);
      glVertex3f(1.7f, 0.0f, 0.0f); 
      glVertex3f(1.7f, 0.8f, 0.0f); 
      glVertex3f(0.8f, 0.8f, 0.0f); 
  glEnd();

  glTranslatef(1.9f,0.0f, 0.0f);

  glBegin(GL_QUADS);
      glVertex3f(0.0f, 0.0f, 0.0f);
      glVertex3f(0.9f, 0.0f, 0.0f); 
      glVertex3f(0.9f, 0.8f, 0.0f); 
      glVertex3f(0.0f, 0.8f, 0.0f); 
  glEnd();

  glBegin(GL_TRIANGLES);
      glVertex3f(0.9f, 0.0f, 0.0f);
      glVertex3f(1.7f, 0.0f, 0.0f); 
      glVertex3f(0.9f, 0.8f, 0.0f); 
  glEnd();

  glPopMatrix();
}

void techo(){

  glPushMatrix();

  glTranslatef(1.0f,1.8f, 0.0f);

  glBegin(GL_TRIANGLES);
      glVertex3f(0.0f, 0.0f, 0.0f);
      glVertex3f(1.0f, 0.0f, 0.0f); 
      glVertex3f(1.0f, 1.0f, 0.0f); 
  glEnd();

  glBegin(GL_QUADS);
      glVertex3f(1.0f, 0.0f, 0.0f);
      glVertex3f(3.0f, 0.0f, 0.0f); 
      glVertex3f(3.0f, 1.0f, 0.0f); 
      glVertex3f(1.0f, 1.0f, 0.0f); 
  glEnd();

  glBegin(GL_TRIANGLES);
      glVertex3f(3.0f, 0.0f, 0.0f);
      glVertex3f(4.0f, 0.0f, 0.0f); 
      glVertex3f(3.0f, 1.0f, 0.0f); 
  glEnd();
  glPopMatrix();
}

void dibujar_cuerpo_coche(){
  glColor3f(1,0,0);  

  glTranslatef(0.0f,0.0f, 0.0f);

  glBegin(GL_POLYGON);
      glVertex3f(-1.0f, 0.0f, 0.0f);
      glVertex3f(7.0f, 0.0f, 0.0f);  
      glVertex3f(9.0f, 0.3f, 0.0f);
      glVertex3f(8.9f, 1.0f, 0.0f); 
      glVertex3f(7.0f, 1.5f, 0.0f); 
      glVertex3f(5.0f, 1.8f, 0.0f); 
      glVertex3f(-1.0f, 1.8f, 0.0f); 
  glEnd();	
  
  glBegin(GL_POLYGON);
      glVertex3f(-0.5f, 1.8f, 0.0f);
      glVertex3f(0.2f, 1.8f, 0.0f); 
      glVertex3f(-0.3f, 2.3f, 0.0f); 
      glVertex3f(-1.2f, 2.3f, 0.0f); 
  glEnd();	
  
}

void dibujar_automovil(){
	
	glTranslatef(posx,0.0f, 0.0f);	
	dibujar_cuerpo_coche();
	techo();
	dibujar_ventanas();
	dibujar_rueda_y_tornillos_delante();
	dibujar_rueda_y_tornillos_detras();
	
}


void display(){
  GLfloat angulo;
  int i; 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	dibujar_automovil();
	glPopMatrix();
	glutSwapBuffers();
}
 
void init(){
  glClearColor(0,0,0,0);
  posicion=1.5;
  grados=0;
  glEnable(GL_DEPTH_TEST);
}

 
void keyboard(unsigned char key, int x, int y){
  switch(key)
    {
    case 'p':
    	posx++;
      display();
      break;
    case 'P':
    	posx--;
      display();
      break;
   
    case 'o':
    case 'O':
      display();
      break;

    case 27:   // escape
      exit(0);
      break;
    }
}

int main(int argc, char **argv){
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowPosition(50, 50);
  glutInitWindowSize(500, 500);
  glutCreateWindow("Practica Calificada");
  init();
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard); 
  glutMainLoop();
  return 0;
}

