/*EspinozaMansillaCarlos-----CC322-----28/Sept/2018*/
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
float posicion;
int grados;

//variable para desplazamiento
float movX=0; 
float ruedacheck=0;
float movXcamion=0;
float ruedacheckcamion=0;

void reshape(int width, int height){
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-10, 10, -10, 10, 0.1f, 20);
  glTranslatef(-3.0f, 0.0f, -15.0f);
  glMatrixMode(GL_MODELVIEW);
}

void dibujar_rueda_delante(){
  glPushMatrix();
  glColor3f(0.1f,0.5f,0.1f);  
  glTranslatef(1.5f,0.0f, 0.0f);
  glutSolidSphere(1.0f,20,20);
  /**********tornillitos******/
  glRotatef(ruedacheck,0.0,0.0,1.0);
  glTranslatef(-0.55f,0.3f, 0.0f);
  glColor3f(0.5f,0.9f,0.0f);
  glutSolidSphere(0.1f, 10, 10);
  
  glTranslatef(0.55f,0.15f, 0.0f);
  glColor3f(0.5f,0.9f,0.0f);
  glutSolidSphere(0.1f, 10, 10);
  
  glTranslatef(0.55f,-0.15f, 0.0f);
  glColor3f(0.5f,0.9f,0.0f);
  glutSolidSphere(0.1f, 10, 10);
  
  glTranslatef(-0.15f,-0.85f, 0.0f);
  glColor3f(0.5f,0.9f,0.0f);
  glutSolidSphere(0.1f, 10, 10);
  
  glTranslatef(-0.7f,0.0f, 0.0f);
  glColor3f(0.5f,0.9f,0.0f);
  glutSolidSphere(0.1f, 10, 10);
  
  /*****************************/
  glPopMatrix();
}

void dibujar_rueda_detras(){
  glPushMatrix();
  glColor3f(0.1f,0.5f,0.1f);  
  glTranslatef(5.5f,0.0f, 3.0f);
  glutSolidSphere(1.0f,20,20); 
  /**********tornillitos******/
  glRotatef(ruedacheck,0.0,0.0,1.0);
  glTranslatef(-0.55f,0.3f, 0.0f);
  glColor3f(0.5f,0.9f,0.0f);
  glutSolidSphere(0.1f, 10, 10);
  
  glTranslatef(0.55f,0.15f, 0.0f);
  glColor3f(0.5f,0.9f,0.0f);
  glutSolidSphere(0.1f, 10, 10);
  
  glTranslatef(0.55f,-0.15f, 0.0f);
  glColor3f(0.5f,0.9f,0.0f);
  glutSolidSphere(0.1f, 10, 10);
  
  glTranslatef(-0.15f,-0.85f, 0.0f);
  glColor3f(0.5f,0.9f,0.0f);
  glutSolidSphere(0.1f, 10, 10);
  
  glTranslatef(-0.7f,0.0f, 0.0f);
  glColor3f(0.5f,0.9f,0.0f);
  glutSolidSphere(0.1f, 10, 10);
  
  /*****************************/
  glPopMatrix();
}

void dibujar_ventanas(){
  glPushMatrix();
  glColor3f(1.0f,0.4f,0.4f);  
  glTranslatef(1.2f,2.0f, 0.01f);
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
  glTranslatef(1.0f,2.0f, 0.0f);
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
  glColor3f(0.6f,0.1f,0.6f);  
  glTranslatef(0.0f,0.0f, 0.0f);
  glBegin(GL_QUADS);
  glVertex3f(0.0f, 0.0f, 0.0f);
  glVertex3f(7.0f, 0.0f, 0.0f); 
  glVertex3f(7.0f, 2.0f, 0.0f); 
  glVertex3f(0.0f, 2.0f, 0.0f); 
  glEnd(); 
  /*****Parachoques******/
  glBegin(GL_TRIANGLES);
  glVertex3f(7.0f, 0.6f, 0.0f);
  glVertex3f(7.0f, 2.0f, 0.0f); 
  glVertex3f(8.0f, 0.6f, 0.0f); 
  glEnd();
  glBegin(GL_QUADS);
  glVertex3f(8.0f, 0.6f, 0.0f);
  glVertex3f(7.0f, 0.6f, 0.0f); 
  glVertex3f(7.0f, 0.0f, 0.0f); 
  glVertex3f(8.0f, 0.0f, 0.0f);  
  glEnd();
  
  /*******parte_trasera********/
  glBegin(GL_TRIANGLES);
  glVertex3f(0.0f, 1.4f, 0.0f);
  glVertex3f(0.0f, 0.0f, 0.0f); 
  glVertex3f(-1.6f, 1.4f, 0.0f); 
  glEnd();
  glBegin(GL_QUADS);
  glVertex3f(-1.6f, 1.4f, 0.0f);
  glVertex3f(0.0f, 1.4f, 0.0f); 
  glVertex3f(0.0f, 2.0f, 0.0f); 
  glVertex3f(-1.6f, 2.0f, 0.0f);  
  glEnd();
  glBegin(GL_QUADS);
  glVertex3f(-0.9f, 2.6f, 0.0f);
  glVertex3f(-0.9f, 2.0f, 0.0f); 
  glVertex3f(-0.5f, 2.0f, 0.0f); 
  glVertex3f(-0.5f, 2.6f, 0.0f);  
  glEnd();
  glBegin(GL_TRIANGLES);
  glVertex3f(-0.3f, 2.6f, 0.0f);
  glVertex3f(-1.3f, 3.1f, 0.0f); 
  glVertex3f(-1.0f, 2.6f, 0.0f); 
  glEnd();

}

void dibujar_rueda_delante_camion(){
  glPushMatrix();
  glColor3f(1.0f,0.5f,0.1f);  
  glTranslatef(1.5f,0.0f, 0.0f);
  glutSolidSphere(1.3f,20,20);
  /**********tornillitos******/
  glRotatef(ruedacheckcamion,0.0,0.0,1.0);
  glTranslatef(-0.55f,0.3f, 0.0f);
  glColor3f(0.5f,0.9f,0.0f);
  glutSolidSphere(0.1f, 10, 10);
  
  glTranslatef(0.55f,0.15f, 0.0f);
  glColor3f(0.5f,0.9f,0.0f);
  glutSolidSphere(0.1f, 10, 10);
  
  glTranslatef(0.55f,-0.15f, 0.0f);
  glColor3f(0.5f,0.9f,0.0f);
  glutSolidSphere(0.1f, 10, 10);
  
  glTranslatef(-0.15f,-0.85f, 0.0f);
  glColor3f(0.5f,0.9f,0.0f);
  glutSolidSphere(0.1f, 10, 10);
  
  glTranslatef(-0.7f,0.0f, 0.0f);
  glColor3f(0.5f,0.9f,0.0f);
  glutSolidSphere(0.1f, 10, 10);
  
  /*****************************/
  glPopMatrix();
}

void dibujar_rueda_detras_camion(){
  glPushMatrix();
  glColor3f(1.0f,0.5f,0.1f);  
  glTranslatef(7.2f,0.0f, 3.0f);
  glutSolidSphere(1.3f,20,20); 
  /**********tornillitos******/
  glRotatef(ruedacheckcamion,0.0,0.0,1.0);
  glTranslatef(-0.55f,0.3f, 0.0f);
  glColor3f(0.5f,0.9f,0.0f);
  glutSolidSphere(0.1f, 10, 10);
  
  glTranslatef(0.55f,0.15f, 0.0f);
  glColor3f(0.5f,0.9f,0.0f);
  glutSolidSphere(0.1f, 10, 10);
  
  glTranslatef(0.55f,-0.15f, 0.0f);
  glColor3f(0.5f,0.9f,0.0f);
  glutSolidSphere(0.1f, 10, 10);
  
  glTranslatef(-0.15f,-0.85f, 0.0f);
  glColor3f(0.5f,0.9f,0.0f);
  glutSolidSphere(0.1f, 10, 10);
  
  glTranslatef(-0.7f,0.0f, 0.0f);
  glColor3f(0.5f,0.9f,0.0f);
  glutSolidSphere(0.1f, 10, 10);
  
  /*****************************/
  glPopMatrix();
}

void dibujar_ventanas_camion(){
  glPushMatrix();
  glColor3f(0.4f,0.4f,1.0f);  
  glTranslatef(1.2f,2.0f, 0.01f);  
  glTranslatef(1.9f,0.0f, 0.0f);
  glBegin(GL_QUADS);
  glVertex3f(4.7f, 0.0f, 0.0f);
  glVertex3f(5.6f, 0.0f, 0.0f); 
  glVertex3f(5.6f, 0.8f, 0.0f); 
  glVertex3f(4.7f, 0.8f, 0.0f); 
  glEnd();
  glBegin(GL_TRIANGLES);
  glVertex3f(5.6f, 0.0f, 0.0f);
  glVertex3f(6.4f, 0.0f, 0.0f); 
  glVertex3f(5.6f, 0.8f, 0.0f); 
  glEnd();
  glPopMatrix();
}

void dibujar_cuerpo_camion(){
  glColor3f(1.0f,1.0f,1.0f);  
  glTranslatef(0.0f,0.0f, 0.0f);
  glBegin(GL_QUADS);
  glVertex3f(0.0f, 0.0f, 0.0f);
  glVertex3f(7.0f, 0.0f, 0.0f); 
  glVertex3f(7.0f, 4.9f, 0.0f); 
  glVertex3f(0.0f, 4.9f, 0.0f); 
  glEnd(); 
  /*****CABINA******/  
  glBegin(GL_QUADS);
  glColor3f(0.6f,0.6f,0.6f);  
  glVertex3f(10.0f, 3.6f, 0.0f);
  glVertex3f(7.0f, 3.6f, 0.0f); 
  glVertex3f(7.0f, 0.0f, 0.0f); 
  glVertex3f(10.0f, 0.0f, 0.0f);  
  glEnd();
  
  /*******parte_trasera********/
  
  glBegin(GL_QUADS);
  glVertex3f(-1.0f, 0.0f, 0.0f);
  glVertex3f(0.0f, 0.0f, 0.0f); 
  glVertex3f(0.0f, 2.0f, 0.0f); 
  glVertex3f(-1.0f, 2.0f, 0.0f);  
  glEnd();  

}


void dibujar_automovil(){
  
  glPushMatrix();
  glTranslatef(movX,4.0f, 0.0f);
  glTranslatef(movX,0.0f, 0.0f);
  dibujar_cuerpo_coche();
  techo();
  dibujar_ventanas();
  dibujar_rueda_delante();
  dibujar_rueda_detras();
  glPopMatrix();
  
  glPushMatrix();
  glTranslatef(0.0f,-5.0f, 0.0f);
  glTranslatef(movXcamion,0.0f, 0.0f);
  dibujar_cuerpo_camion();
  dibujar_ventanas_camion();
  dibujar_rueda_delante_camion();
  dibujar_rueda_detras_camion();
  glPopMatrix();
  

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
  switch(key){
    case 'p':case 'P':
    display();
    break;
    case 'o':case 'O':
    display();
    break;
    case 'a':case'A':
    movX = movX - 0.6; 
    ruedacheck = ruedacheck + 15;
    display();
    break;  
    case 'd':case'D':
    movX = movX + 0.6;
    ruedacheck = ruedacheck -15; 
    display();
    break;
    case 'j':case'J':
    movXcamion = movXcamion - 2.5; 
    ruedacheckcamion = ruedacheckcamion + 30;
    display();
    break;  
    case 'l':case'L':
    movXcamion = movXcamion + 2.5;
    ruedacheckcamion = ruedacheckcamion -30; 
    display();
    break;     
    case 27:   
    // escape
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
  printf("a,d: Para controlar al auto\nj,l: Para controlar al camion\n\n\n");
  glutMainLoop();
  return 0;
}


