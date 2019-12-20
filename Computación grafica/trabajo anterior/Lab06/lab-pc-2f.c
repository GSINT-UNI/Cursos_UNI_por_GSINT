#include <GL/glut.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include <stdio.h> 

float posicion;
int grados;
float posx=0;
float psx=0;
float t=0;
int obs_act=0;
float inicio=0;
int mov1=1;
int mov2=1;


void reshape(int width, int height){
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-10, 10, -10, 10, 0.1f, 20);
  glTranslatef(-3.0f, 0.0f, -15.0f);
  glMatrixMode(GL_MODELVIEW);
}


void dibujar_rueda_y_tornillos_delante(float pos){
  glPushMatrix();
  glColor3f(0.5f,0.5f,0.5f);  
  glTranslatef(1.5f,0.0f, 0.0f);
  glutSolidSphere(1.0f,20,20);
  glRotatef(-pos*180/3.1416,0,0,1);//para girar las llantas
  
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

void dibujar_rueda_y_tornillos_detras(float pos){
  glPushMatrix();
  glColor3f(0.5f,0.5f,0.5f);  
  glTranslatef(5.5f,0.0f, 3.0f);
  glutSolidSphere(1.0f,20,20);
  glRotatef(-pos*180/3.1416,0,0,1);//para girar las llantas
  
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
  
  glTranslatef(-5.0f,0.0f, 0.0f);

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

void dibujar_automovil(float pos){
	
	dibujar_cuerpo_coche();
	techo();
	dibujar_ventanas();
	dibujar_rueda_y_tornillos_delante(pos);
	dibujar_rueda_y_tornillos_detras(pos);
	
}

int verificar(float x,float y){
	if(y==1&&obs_act==1){
		if(x>1.5f&&x<14.8f)
			return 0;
		else return 1;
	}else{
		if(y==-4.0&&obs_act==1){
			if(x>2.4f&&x<15.9){
				printf("ppppppppppppppppppppppsx %f",x);
				return 0;
			}
		}else	return 1;
	}
	return 1;
	
	
}

void dibujar_obstaculo(){
	if(inicio+10 == t){
		obs_act=0;
		mov1=1;
		mov2=1;
	}
	glPushMatrix();
  	glTranslatef(0.0f,0.0f, 0.0f);

  glBegin(GL_POLYGON);
	glColor3f(1,0.8,0);
      glVertex3f(7.0f, -7.0f, 0.0f);
      glVertex3f(10.0f, -7.0f, 0.0f);
      glVertex3f(10.0f, -5.0f, 0.0f);
      glVertex3f(7.0f, -5.0f, 0.0f);
  glEnd();
  
  glBegin(GL_POLYGON);
	glColor3f(1,1,0);
      glVertex3f(10.0f, -5.0f, 0.0f);
      glVertex3f(8.0f, 5.0f, 0.0f);
      glVertex3f(5.0f, 5.0f, 0.0f);
      glVertex3f(7.0f, -5.0f, 0.0f);
      
  glEnd();	
  	
  glBegin(GL_POLYGON);
	glColor3f(1,0.7,0);
      glVertex3f(7.0f, -7.0f, 0.0f);
      glVertex3f(7.0f, -5.0f, 0.0f);
      glVertex3f(5.0f, 5.0f, 0.0f);
      glVertex3f(5.0f, 3.0f, 0.0f);
      
  glEnd();	
  	glPopMatrix();
  
}

void display(){
  GLfloat angulo;
  t++;
  int i;
  	mov1=verificar(posx,1.0);
  	mov2=verificar(psx,-4.0);
  	if(obs_act==0&&rand()%10==0){
  		obs_act=1;
  		inicio=t;
  		mov1=0;
  		mov2=0;
  	}
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	if (obs_act==1){
		dibujar_obstaculo();	
	}
	
	glPushMatrix();
	glTranslatef(posx,1.0f, 0.0f);
	glColor3f(1,0,0);  
	dibujar_automovil(posx);
	glPopMatrix();
	
	glColor3f(0,0.7,0.2);  
	glPushMatrix();
	glTranslatef(psx,-4.0f, 0.0f);
	dibujar_automovil(psx);
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
    	if(mov1==1){
	    posx=posx+0.1;
          printf("posx1 %f\n",posx);
      }
      display();
      break;
    case 'P':
    	if(mov1==1){
	    posx=posx-0.1;
          printf("posx1 %f\n",posx);
      }display();
      break;
   
    case 'o':
    	if(mov2==1){
    	    psx=psx+0.3;
          printf("posx2 %f\n",psx);
      }display();
      break;
    case 'O':
    	if(mov2==1){
    	    psx=psx-0.3;
          printf("posx2 %f\n",psx);
      }display();
      break;
    case 'q':
    case 27:   // escape
      exit(0);
      break;
    }
}

int main(int argc, char **argv){
  srand (time(NULL));
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

