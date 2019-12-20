/*
OPERACION CHAVIN DE HUANTAR
*/

#include "texturas.cpp"
#include <iostream>
#include <string>
#include <sstream>
#include "Camera.cpp"
#include "math.h"
#include "GL/glut.h"
#include "Lista.cpp"

using namespace std;

void Display();
void Reshape(int w,int h);
void Keyboard (unsigned char key, int x, int y);
void KeyboardUp(unsigned char key, int x, int y);
void MouseMotion(int x, int y);
void Mouse(int button, int state, int x, int y);
void Timer(int value);
void Idle();
void Init();
bool colitionTest();
void refreshColition();
void refreshColition(float x, float y, float z);
void iniciar_colisiones();
void mover(char m, float inc);
void switch_list(Lista l1, Lista l2);
bool mansion_colition(Lista l);
bool mansion_colition(Elemento* e);
Camera g_camera;
bool g_key[256];
bool g_shift_down = false;
int g_viewport_width = 0;
int g_viewport_height = 0;
bool g_mouse_left_down = false;
bool g_mouse_right_down = false;
float sigilo = 0.3;
bool v3raP = false;
bool aire = false;


// Movement settings
const float g_translation_speed = 0.08;
const float g_rotation_speed = M_PI/180*0.2;

#define QUANT_BULLETS 36
#define QUANT_MANSION 60
#define QUANT_STARES 30
#define QUANT_FLOORS 10

Bala* bullet[QUANT_BULLETS];
Bloque* mansion[QUANT_MANSION];
Piso* escalera[QUANT_STARES];

//lista de pisos
Piso suelo(-50,0,-50,100,100);
//Piso piso_1(2,1.5,-18,20,34);
Piso* floors[QUANT_FLOORS];
bool terror1 =true;
bool terror2 =true;
bool terror3 =true;

class BitmapPrinter {

// ***** BitmapPrinter: public functions *****
public:

    // Ctor (0, 1, 2, or 3 params)
    // Set cursx, cursy, lineht to the given values.
    BitmapPrinter(double theCursx = 0.,
                  double theCursy = 0.,
                  double theLineht = 0.1)
    { setup(theCursx, theCursy, theLineht); }

    // Compiler-generated copy ctor, copy =, dctor used

    // setup
    // Set cursx, cursy, lineht to the given values.
    void setup(double theCursx,
               double theCursy,
               double theLineht = 0.1)
    { cursx = theCursx; cursy = theCursy; lineht = theLineht; }

    // print
    // Draw the given string, using glutBitmapCharacter, with GLUT's
    // 9x15 font, at cursx, cursy, and then reduce cursy by lineht
    // (i.e., move to the next line).
    //
    // The model/view transformation should probably be the identity
    // (or just translations) when calling this function.
    void print(const std::string & msg)
    {
        glRasterPos2d(cursx, cursy);
        for (std::string::const_iterator ii = msg.begin();
             ii != msg.end();
             ++ii)
        {
            glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *ii);
        }
        cursy -= lineht;
    }

// ***** BitmapPrinter: data members *****
private:

    double cursx, cursy;  // Initial raster pos for text line: x, y
    double lineht;        // How much to reduce cursy each line

};  // End class BitmapPrinter



int main (int argc, char **argv) {
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
   glutInitWindowPosition(0,0);
   glutInitWindowSize(600, 500);
   glutCreateWindow("OPERACION CHAVIN DE HUANTAR");

   Init();
   loadTextures();

   //esconde el mouse en el medio
   glutSetCursor(GLUT_CURSOR_NONE);

   glutIgnoreKeyRepeat(1);

   glutDisplayFunc(Display);
   glutReshapeFunc(Reshape);
   glutMouseFunc(Mouse);
   glutMotionFunc(MouseMotion);
   glutPassiveMotionFunc(MouseMotion);
   glutKeyboardFunc(Keyboard);
   glutKeyboardUpFunc(KeyboardUp);
   glutIdleFunc(Idle);

   glutTimerFunc(1, Timer, 0);
   glutMainLoop();

   return 0;
}

void dibujar_arma(float x,float y,float z){
   glPushMatrix();
   glTranslatef(x,y,z);
   glScalef(0.08,0.06,0.05);
   glRotatef(10,1,0,0);
   glRotatef(5,0,0,-1);
   glBegin(GL_QUADS);

   glColor3f(0,0,0);
   glVertex3f(-1,0,-1);
   glVertex3f(-1,0,1);
   glVertex3f(1,0,1);
   glVertex3f(1,0,-1);

   glColor3f(0,0,0);
   glVertex3f(-1,0,1);
   glVertex3f(1,0,1);
   glVertex3f(1,5,1);
   glVertex3f(-1,5,1);

   glColor3f(0.5,0.5,0.5);
   glVertex3f(-1,0,-1);
   glVertex3f(-1,0,1);
   glVertex3f(-1,5,1);
   glVertex3f(-1,5,-1);

   glColor3f(0.5,0.5,0.5);
   glVertex3f(1,0,1);
   glVertex3f(1,0,-1);
   glVertex3f(1,4,-1);
   glVertex3f(1,4,1);

   glColor3f(0,0,0);
   glVertex3f(-1,0,-1);
   glVertex3f(1,0,-1);
   glVertex3f(1,5,-1);
   glVertex3f(-1,5,-1);

   glColor3f(0.5,0.5,0.5);
   glVertex3f(1,4,-1);
   glVertex3f(1,4,1);
   glVertex3f(5,4,1);
   glVertex3f(5,4,-1);

   glColor3f(0.5,0.5,0.5);
   glVertex3f(-1,5,-1);
   glVertex3f(-1,5,1);
   glVertex3f(5,5,1);
   glVertex3f(5,5,-1);

   glColor3f(0,0,0);
   glVertex3f(5,5,-1);
   glVertex3f(5,4,-1);
   glVertex3f(1,4,-1);
   glVertex3f(1,5,-1);

   glColor3f(0,0,0);
   glVertex3f(5,5,1);
   glVertex3f(5,4,1);
   glVertex3f(1,4,1);
   glVertex3f(1,5,1);

   glVertex3f(5,5,1);
   glVertex3f(5,4,1);
   glVertex3f(5,4,-1);
   glVertex3f(5,5,-1);

   glEnd();


   glPopMatrix();
}

void dibujar_bala(){
   float tx,ty,tz;
   float vx,vy,vz;
   for (int i=0;i< QUANT_BULLETS;i++){
      bullet[i]->b->getPos(tx,ty,tz);
      glPushMatrix();
      glTranslatef(tx,ty,tz);
      glutWireSphere(0.02,15,15);
      glPopMatrix();
   }
}

void Grid(){
   glColor3f(1,1,1);
   float dim = 12.5;
   int num = 4;
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, texID[3] );
   glBegin(GL_QUADS);
   glTexCoord2f(0,0);
   glVertex3f(-4*dim,0,4*dim);
   glTexCoord2f(num*dim,0);
   glVertex3f(4*dim,0,4*dim);
   glTexCoord2f(num*dim,num*dim);
   glVertex3f(4*dim,0,-4*dim);
   glTexCoord2f(0,num*dim);
   glVertex3f(-4*dim,0,-4*dim);
   glEnd();
   glDisable(GL_TEXTURE_2D);
}

void cursor(void){
  float vec[3];
  float pos[3];
  g_camera.GetDirectionVector(vec[0],vec[1],vec[2]);
  g_camera.GetPos(pos[0],pos[1],pos[2]);
  glLineWidth(2);

  glPushMatrix();

  glTranslatef(pos[0]+vec[0],pos[1]+vec[1],pos[2]+vec[2]);
  glRotatef(g_camera.GetYaw()*180/M_PI,0,-1,0);
  glRotatef(g_camera.GetPitch()*180/M_PI,0,0,1);

  glColor3f(1,0,0);

  /*

  GLUquadric *quadratic;

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texID[1]);

  quadratic = gluNewQuadric();
  gluQuadricNormals(quadratic, GLU_SMOOTH);
  gluQuadricTexture(quadratic, GL_TRUE);
  gluSphere(quadratic,0.1,40,40);

  */
  glBegin(GL_LINES);
  glVertex3f(0,0,0.05);
  glVertex3f(0,0,0.02);

  glVertex3f(0,0,-0.05);
  glVertex3f(0,0,-0.02);

  glVertex3f(0,0.05,0);
  glVertex3f(0,0.02,0);

  glVertex3f(0,-0.05,0);
  glVertex3f(0,-0.02,0);

  glEnd();

  //glutWireTeapot(0.5);

  glPopMatrix();
  glLineWidth(1);
}

int bala_act = 0;
void personaje(){

   float vec[3];
   float pos[3];
   g_camera.GetDirectionVector(vec[0],vec[1],vec[2]);
   g_camera.GetPos(pos[0],pos[1],pos[2]);
   glPushMatrix();

   glTranslatef(pos[0],pos[1],pos[2]);
   glRotatef(g_camera.GetYaw()*180/M_PI,0,-1,0);

   /*
   glutWireTeapot(0.5);
   */
   glPushMatrix();
   if(v3raP){
      glColor3f(0,0,1);
      glutWireSphere(0.5,15,15);
      glTranslatef(0,-0.5,0);
      glutWireSphere(0.5,15,15);
      glTranslatef(0,-0.5,0);
      glutWireSphere(0.5,15,15);
      glTranslatef(0,-0.5,0);
      glutWireSphere(0.5,15,15);
   }
   glPopMatrix();

   glRotatef(g_camera.GetPitch()*180/M_PI,0,0,1);
   dibujar_arma(0.5,-0.4,0.3);
   if(v3raP==false){
      string w= "CANTIDAD DE BALAS: "+static_cast<std::ostringstream*>(&(std::ostringstream() << QUANT_BULLETS-bala_act))->str();
      glTranslatef(1.3,0.5,-0.2);
      glColor3d(0., 0., 0.);        // Black text
      BitmapPrinter p(-0.9,-0.7, 0.1);
      p.print(w);
   }
   glPopMatrix();
   glColor3f(0,0,0);
}

void Init(){
   glClearColor (1,1,1,1.0);
   glEnable(GL_DEPTH_TEST);
/*
      GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   GLfloat position[] = { 5, 5, 5, 1 };
   GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat lmodel_ambient[] = { 0.4, 0.4, 0.4, 1.0 };
   GLfloat local_view[] = { 0.0 };
   glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
   glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
   glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
   glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);
   glLightfv(GL_LIGHT0, GL_POSITION, position);
*/
   for (int i=0;i< QUANT_BULLETS;i++){
      bullet[i] = new Bala(0,0,0,0,0,0);
   }
   //construccion de la mansion
   int i=0;
   mansion[i++]= new Bloque(0,0,-18,2,7,5);
   mansion[i++]= new Bloque(0,0,-10,2,7,5);
   mansion[i++]= new Bloque(0,0,-13,2,2,3);
   mansion[i++]= new Bloque(0,5,-13,2,2,3);

   mansion[i++]= new Bloque(0,0,3,2,7,5);
   mansion[i++]= new Bloque(0,0,11,2,7,5);
   mansion[i++]= new Bloque(0,0,8,2,2,3);
   mansion[i++]= new Bloque(0,5,8,2,2,3);

   mansion[i++]= new Bloque(-2,0,-5.7 ,0.7,7,0.7);
   mansion[i++]= new Bloque(-2,0,3 ,0.7,7,0.7);

   mansion[i++]= new Bloque(0,0,-19, 15,7,1);
   mansion[i++]= new Bloque(18,0,-19, 4,7,1);
   mansion[i++]= new Bloque(15,5,-19, 3,2,1);

   mansion[i++]= new Bloque(0,0,16, 22,7,1);

   mansion[i++]= new Bloque(22,0,-19, 1,7,10);
   mansion[i++]= new Bloque(22,0,-9, 1,3,4);
   mansion[i++]= new Bloque(22,6,-9, 1,1,4);
   mansion[i++]= new Bloque(22,0,-5, 1,7,10);
   mansion[i++]= new Bloque(22,0,5, 1,3,4);
   mansion[i++]= new Bloque(22,6,5, 1,1,4);
   mansion[i++]= new Bloque(22,0,9, 1,7,8);
//segundo piso
   mansion[i++]= new Bloque(2,7,-18, 20,0.5,8);
   mansion[i++]= new Bloque(2,7,-10, 10,0.5,8);
   mansion[i++]= new Bloque(2,7,-2, 20,0.5,18);
   mansion[i++]= new Bloque(12,7,-8, 10,0.5,6);
//barandal
   mansion[i++]= new Bloque(11,1.6,-10.5, 8,5.4,0.5);
   mansion[i++]= new Bloque(11,1.6,-8, 8,5.4,0.5);
//muros 2do Piso
   mansion[i++]= new Bloque(0,7,-18,2,7,5);
   mansion[i++]= new Bloque(0,7,-10,2,7,6);
   mansion[i++]= new Bloque(0,7,-13,2,2,3);
   mansion[i++]= new Bloque(0,12,-13,2,2,3);

   mansion[i++]= new Bloque(0,7,2,2,7,6);
   mansion[i++]= new Bloque(0,7,11,2,7,5);
   mansion[i++]= new Bloque(0,7,8,2,2,3);
   mansion[i++]= new Bloque(0,12,8,2,2,3);

   mansion[i++]= new Bloque(0,7,-19, 15,7,1);
   mansion[i++]= new Bloque(18,7,-19, 4,7,1);
   mansion[i++]= new Bloque(15,12,-19, 3,2,1);

   mansion[i++]= new Bloque(0,7,16, 22,7,1);

   mansion[i++]= new Bloque(22,7,-19, 1,7,10);
   mansion[i++]= new Bloque(22,7,-9, 1,3,4);
   mansion[i++]= new Bloque(22,13,-9, 1,1,4);
   mansion[i++]= new Bloque(22,7,-5, 1,7,10);
   mansion[i++]= new Bloque(22,7,5, 1,3,4);
   mansion[i++]= new Bloque(22,13,5, 1,1,4);
   mansion[i++]= new Bloque(22,7,9, 1,7,8);
//techo
   mansion[i++]= new Bloque(0,14,-19, 20,0.5,34.5);
//caja
   mansion[i++]= new Bloque(23,0,5, 1.5,1.5,1.5);


   mansion[i++]= new Bloque(10,1.5,10, 1,2,1);

   mansion[i++]= new Bloque(7,1.5,-10, 1,2,1);

   mansion[i++]= new Bloque(12,1.5,2, 1,2,1);

   mansion[i++]= new Bloque(12,7.5,2, 1,2,1);

   //construccion de escaleras
   for (i=0;i<3;i++){
      escalera[i] = new Piso(i-2,0.5*(i+1),-5, 0.3,8);
   }

   for (i=3;i<6;i++){
      escalera[i] = new Piso(15,0.5*(i-2),-24+i, 3,0.3);
   }

   for (i=6;i<14;i++){
      escalera[i] = new Piso(i+5,2.3+0.7*(i-6),-10, 0.3,2);
   }

   //construccion de pisos
   floors[0] = new Piso(2,1.5,-18, 20,34);
   floors[1] = new Piso(1,1.5,-5, 1,8);
   floors[2] = new Piso(-3,7.5,-6, 5,10);
   floors[3] = new Piso(19,7.5,-10, 3,2);


   //incio de posicion
   g_camera.SetPos(-10,2,0);
   iniciar_colisiones();
}


void cubo(){
      glColor3f(1,1,1);
      float lado = 0.5;
      glEnable(GL_TEXTURE_2D);
      glBindTexture(GL_TEXTURE_2D, texID[1] );
       glBegin(GL_QUADS);
   	glTexCoord2f(0,0);
   	glVertex3f(-2*lado,0,2*lado);
   	glTexCoord2f(0.5,0);
   	glVertex3f(-2*lado,0,-2*lado);
         glTexCoord2f(0.5,1);
         glVertex3f(-2*lado,4*lado,-2*lado);
         glTexCoord2f(0,1);
         glVertex3f(-2*lado,4*lado,2*lado);

         glTexCoord2f(0.5,0);
         glVertex3f(-2*lado,0,-2*lado);
         glTexCoord2f(1,0);
         glVertex3f(2*lado,0,-2*lado);
         glTexCoord2f(1,1);
         glVertex3f(2*lado,4*lado,-2*lado);
         glTexCoord2f(0.5,1);
         glVertex3f(-2*lado,4*lado,-2*lado);

         glTexCoord2f(1,0);
         glVertex3f(2*lado,0,-2*lado);
         glTexCoord2f(0.5,0);
         glVertex3f(2*lado,0,2*lado);
         glTexCoord2f(0.5,1);
         glVertex3f(2*lado,4*lado,2*lado);
         glTexCoord2f(1,1);
         glVertex3f(2*lado,4*lado,-2*lado);

         glTexCoord2f(0.5,0);
         glVertex3f(2*lado,0,2*lado);
         glTexCoord2f(0,0);
         glVertex3f(-2*lado,0,2*lado);
         glTexCoord2f(0,1);
         glVertex3f(-2*lado,4*lado,2*lado);
         glTexCoord2f(0.5,1);
         glVertex3f(2*lado,4*lado,2*lado);

         glTexCoord2f(0.5,0.5);
         glVertex3f(-2*lado,4*lado,-2*lado);
         glTexCoord2f(1,0.5);
         glVertex3f(2*lado,4*lado,-2*lado);
         glTexCoord2f(1,1);
         glVertex3f(2*lado,4*lado,2*lado);
         glTexCoord2f(0.5,1);
         glVertex3f(-2*lado,4*lado,2*lado);

         glEnd();
      glDisable(GL_TEXTURE_2D);
}

void dibujar_cubo(float * v,int id,float* v2){
   float a,b,c;
   a= v2[0];
   b= v2[1];
   c= v2[2];
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, texID[id] );
   glColor3f(1,1,1);
   glPushMatrix();
   glTranslatef(v[0],v[1],v[2]);
   glBegin(GL_QUADS);
   //cara de abajo
   glTexCoord2f(0,0);
   glVertex3f(0,0,0);
   glTexCoord2f(1,0);
   glVertex3f(0,0,c);
   glTexCoord2f(1,1);
   glVertex3f(a,0,c);
   glTexCoord2f(0,1);
   glVertex3f(a,0,0);
   //cara de la izquierda
   glTexCoord2f(0,0);
   glVertex3f(0,0,0);
   glTexCoord2f(1,0);
   glVertex3f(a,0,0);
   glTexCoord2f(1,1);
   glVertex3f(a,b,0);
   glTexCoord2f(0,1);
   glVertex3f(0,b,0);
   //cara de la derecha
   glTexCoord2f(0,0);
   glVertex3f(0,0,c);
   glTexCoord2f(1,0);
   glVertex3f(a,0,c);
   glTexCoord2f(1,1);
   glVertex3f(a,b,c);
   glTexCoord2f(0,1);
   glVertex3f(0,b,c);
   //cara de adelante
   glTexCoord2f(0,0);
   glVertex3f(0,0,0);
   glTexCoord2f(1,0);
   glVertex3f(0,0,c);
   glTexCoord2f(1,1);
   glVertex3f(0,b,c);
   glTexCoord2f(0,1);
   glVertex3f(0,b,0);
   //cara de atras
   glTexCoord2f(0,0);
   glVertex3f(a,0,0);
   glTexCoord2f(1,0);
   glVertex3f(a,0,c);
   glTexCoord2f(1,1);
   glVertex3f(a,b,c);
   glTexCoord2f(0,1);
   glVertex3f(a,b,0);
   //cara de arriba
   glTexCoord2f(0,0);
   glVertex3f(0,b,0);
   glTexCoord2f(1,0);
   glVertex3f(0,b,c);
   glTexCoord2f(1,1);
   glVertex3f(a,b,c);
   glTexCoord2f(0,1);
   glVertex3f(a,b,0);

   glEnd();
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}

void dibujar_piso(float * v,int id,float* v2, int n){
   float a,b,c;
   a= v2[0];
   b= v2[1];
   c= v2[2];
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, texID[id] );
   glColor3f(1,1,1);
   glPushMatrix();
   glTranslatef(v[0],v[1],v[2]);
   glBegin(GL_QUADS);

   glTexCoord2f(0,0);
      glVertex3f(0,b,0);
      glTexCoord2f(1*n,0);
      glVertex3f(0,b,c);
      glTexCoord2f(1*n,1*n);
      glVertex3f(a,b,c);
      glTexCoord2f(0,1*n);
      glVertex3f(a,b,0);

      glEnd();
      glPopMatrix();
      glDisable(GL_TEXTURE_2D);
}

//cajas
Bloque mapa(-50,0,-50,100,100,100);


void Display (void) {
   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   if(v3raP)
      g_camera.Refresh3p();
   else
      g_camera.Refresh();

   colitionTest();

   Grid();//cesped
   glutWireTeapot(0.5);

   personaje();

   cursor();
   glColor3f(0,0,0);
   dibujar_bala();


/*
   glPushMatrix();
   glTranslatef(5,2,0);
   glutWireSphere(0.5,15,15);
   glTranslatef(0,-0.5,0);
   glutWireSphere(0.5,15,15);
   glTranslatef(0,-0.5,0);
   glutWireSphere(0.5,15,15);
   glTranslatef(0,-0.5,0);
   glutWireSphere(0.5,15,15);
   glPopMatrix();
*/

   //cielo
   glPushMatrix();
   glScalef(50,50,50);
   cubo();
   glPopMatrix();

   float v[3],v1[3];
   //pisos
   //primer piso
   floors[0]->getPos(v[0],v[1],v[2]);
   floors[0]->getBounds(v1[0],v1[2]);
   v1[1]=0.5;
   v[1]-=v1[1];
   dibujar_piso(v,4,v1,21);

   floors[1]->getPos(v[0],v[1],v[2]);
   floors[1]->getBounds(v1[0],v1[2]);
   v1[1]=0.5;
   v[1]-=v1[1];
   dibujar_piso(v,0,v1,21);

   floors[2]->getPos(v[0],v[1],v[2]);
   floors[2]->getBounds(v1[0],v1[2]);
   v1[1]=0.7;
   v[1]-=v1[1];
   dibujar_cubo(v,0,v1);

   //segundo piso
   floors[3]->getPos(v[0],v[1],v[2]);
   floors[3]->getBounds(v1[0],v1[2]);
   v1[1]=0.5;
   v[1]-=v1[1];
   dibujar_cubo(v,0,v1);

//mansion muros
   for (int i=0;i<21;i++){
      if(mansion[i]!=NULL){
         mansion[i]->getPos(v[0],v[1],v[2]);
         mansion[i]->getBounds(v1[0],v1[1],v1[2]);
         dibujar_cubo(v, 5 ,v1);
      }
   }
   for (int i=21;i<25;i++){
      if(mansion[i]!=NULL){
         mansion[i]->getPos(v[0],v[1],v[2]);
         mansion[i]->getBounds(v1[0],v1[1],v1[2]);
         dibujar_cubo(v, 0 ,v1);
      }
   }
   for (int i=25;i<46;i++){
      if(mansion[i]!=NULL){
         mansion[i]->getPos(v[0],v[1],v[2]);
         mansion[i]->getBounds(v1[0],v1[1],v1[2]);
         dibujar_cubo(v, 5 ,v1);
      }
   }

   mansion[46]->getPos(v[0],v[1],v[2]);
   mansion[46]->getBounds(v1[0],v1[1],v1[2]);
   dibujar_cubo(v, 5 ,v1);

      mansion[47]->getPos(v[0],v[1],v[2]);
      mansion[47]->getBounds(v1[0],v1[1],v1[2]);
      dibujar_cubo(v, 4 ,v1);

   if(terror1 == true){
      mansion[48]->getPos(v[0],v[1],v[2]);
      mansion[48]->getBounds(v1[0],v1[1],v1[2]);
      dibujar_cubo(v, 8 ,v1);
   }

   if(terror2 == true){
      mansion[49]->getPos(v[0],v[1],v[2]);
      mansion[49]->getBounds(v1[0],v1[1],v1[2]);
      dibujar_cubo(v, 9 ,v1);
   }

   mansion[50]->getPos(v[0],v[1],v[2]);
   mansion[50]->getBounds(v1[0],v1[1],v1[2]);
   dibujar_cubo(v, 10 ,v1);

   if(terror3 == true){
      mansion[51]->getPos(v[0],v[1],v[2]);
      mansion[51]->getBounds(v1[0],v1[1],v1[2]);
      dibujar_cubo(v, 9 ,v1);
   }
//escaleras
   for (int i=0;i<3;i++){
      if(escalera[i]!=NULL){
         escalera[i]->getPos(v[0],v[1],v[2]);
         escalera[i]->getBounds(v1[0],v1[2]);
         v1[1]=0.5;
         v[1]=v[1]-v1[1];
         v1[0]+=0.7;
         dibujar_cubo(v,0,v1);
      }
   }

   for (int i=3;i<6;i++){
      if(escalera[i]!=NULL){
         escalera[i]->getPos(v[0],v[1],v[2]);
         escalera[i]->getBounds(v1[0],v1[2]);
         v1[1]=0;
         v[1]=v[1]-v1[1];
         v1[2]+=0.7;
         dibujar_cubo(v,0,v1);
      }
   }

   for (int i=6;i<14;i++){
      if(escalera[i]!=NULL){
         escalera[i]->getPos(v[0],v[1],v[2]);
         escalera[i]->getBounds(v1[0],v1[2]);
         v1[1]=0.7;
         v[1]=v[1]-v1[1];
         v1[0]+=0.7;
         dibujar_cubo(v,0,v1);
      }
   }


   glutSwapBuffers(); //swap the buffers
}

void Reshape (int w, int h) {
    g_viewport_width = w;
    g_viewport_height = h;

    glViewport (0, 0, (GLsizei)w, (GLsizei)h); //set the viewport to the current window specifications
    glMatrixMode (GL_PROJECTION); //set the matrix to projection

    glLoadIdentity ();
    gluPerspective (60, (GLfloat)w / (GLfloat)h, 0 , 500.0); //set the perspective (angle of sight, width, height, ,depth)
    glMatrixMode (GL_MODELVIEW); //set the matrix back to model
    glLoadIdentity ();

}

void KeyboardUp(unsigned char key, int x, int y){
   if(key=='w' || key=='W') {
      g_key['w'] = false;
      g_key['W'] = false;
   }
   if(key=='s' || key=='S') {
      g_key['s'] = false;
      g_key['S'] = false;
   }
   if(key=='a' || key=='A') {
      g_key['a'] = false;
      g_key['A'] = false;
   }
   if(key=='d' || key=='D') {
      g_key['d'] = false;
      g_key['D'] = false;
   }
   if(key=='<'){
      g_key['<'] = false;
      if(g_camera.GetY()>2){
         g_camera.setHeight(g_camera.GetY() +1);
      }else{
         g_camera.setHeight(2);
      }
   }
   g_key[key]=false;
}

const float g=0.00000987;
float v=0;
float t=0;

void Keyboard(unsigned char key, int x, int y){
   if(key == 27) {
      exit(0);
   }
   if(key == '<') {
      g_camera.setHeight(g_camera.GetY()-1);
   }
   if(key == ' ' && aire==false) {
      //aire = true;
      v=0.00464*1.5;
      t=0;
      g_camera.setHeight(g_camera.GetY()+0.000101);
      refreshColition();
   }
   if(key == 'f') {
      v3raP = !v3raP;
   }
   glutWarpPointer(g_viewport_width/2, g_viewport_height/2);

   if(glutGetModifiers() == GLUT_ACTIVE_SHIFT) {
      g_shift_down = true;
   }
   else {
      g_shift_down = false;
   }

   g_key[key] = true;
}

float velocidad (){
   if (t>3)
      return v = v - g*t;
   else
      return v;
}

Lista lpersonaje;
Lista lsig;

bool compare_floor(Lista l, Piso &p){
   float x,y,z;
   Elemento* act = l.inicio;
   for (int i = 0; i < l.tam && act!=NULL; i++){
      if (Piso::compare(p,*act)){
         return true;
      }
      act= act->sig;
   }
   return false;
}

bool test_gravity(Lista l, Piso &p){
   float x,y,z;
   g_camera.GetPos(x,y,z);
   refreshColition(x,y-0.00001,z);
   bool resp = compare_floor(l,p);
   if(resp == true){
      if( y >= p.getY()){
         g_camera.SetPos(x,p.getY()+2.00001,z);
         aire = false;

      }
      else {
         g_camera.SetPos(x,p.getY()-0.5,z);
      }

      refreshColition();
      switch_list(lpersonaje,lsig);
   }
   return resp;
}



bool test_g(Lista l, Bloque blq){
   float x,y,z;
   g_camera.GetPos(x,y,z);
   refreshColition(x,y-0.00001,z);
   bool resp = blq.compare_floor(l);
   if(blq.compare_floor(l) == true){
      if( y >= blq.pA->getY()){
         g_camera.SetPos(x,blq.pA->getY()+2.00001,z);
         aire = false;

      }
      else {
         g_camera.SetPos(x,blq.pa->getY()-0.5,z);
      }

      refreshColition();
      switch_list(lpersonaje,lsig);
   }
   return resp;

}


bool test_mansion(Lista l){
   int i=0;
   while(mansion[i] != NULL){
      if(test_g(l,*mansion[i])){
         return true;
      }
      i++;
   }
   return false;
}

bool test_mansion(Elemento* e){
   int i=0;
   while(mansion[i] != NULL){
      if(mansion[i]->compare_floor(e)){
         return true;
      }
      i++;
   }
   return false;
}

bool test_stares(Lista l){
   int i=0;
   while(escalera[i] != NULL){
      if(test_gravity(l,*escalera[i])){
         return true;
      }
      i++;
   }
   return false;
}

bool test_stares(Elemento* e){
   int i=0;
   while(escalera[i] != NULL){
      if(Piso::compare(*escalera[i],*e)){
         return true;
      }
      i++;
   }
   return false;
}

bool test_floors(Lista l){
   int i=0;
   while(floors[i] != NULL){
      if(test_gravity(l,*floors[i])){
         return true;
      }
      i++;
   }
   return false;
}

bool test_floors(Elemento* e){
   int i=0;
   while(floors[i] != NULL){
      if(Piso::compare(*floors[i],*e)){
         return true;
      }
      i++;
   }
   return false;
}

void gravedad(){
   if(test_stares(lsig)){
      //toca el suelo
      v=0;
      t=0;
   }
   else{
      if(test_floors(lsig)||test_mansion(lsig)||test_gravity(lsig,suelo)){
            v=0;
            t=0;
      }
      else{
         g_camera.setHeight(g_camera.GetY() +velocidad()*t-g*t*t/2);
         refreshColition();
         switch_list(lpersonaje,lsig);
         aire = true;
      }
   }
}

void try_colition(Bala* bll){
   float x,y,z;
   float vx,vy,vz;
   float inc = 0.1;
   bll->b->getPos(x,y,z);
   while(bll->viva){
      bll->getdir(vx,vy,vz);
      x+=inc*vx;
      y+=inc*vy;
      z+=inc*vz;
      if(mansion_colition(bll->b)||mapa.colition_test(bll->b)){
         bll->viva = false;
      }else{
         if(test_mansion(bll->b)||test_stares(bll->b)||test_floors(bll->b)||Piso::compare(suelo,*bll->b)||mapa.compare_floor(bll->b)){
            bll->viva = false;
         }
         else{
            bll->b->setPos(x,y,z);
            if(mansion[48]->compare_floor(bll->b)||mansion[48]->colition_test(bll->b)){
               terror1 = false;
            }
            if(mansion[49]->compare_floor(bll->b)||mansion[49]->colition_test(bll->b)){
               terror2 = false;
            }
            if(mansion[50]->compare_floor(bll->b)||mansion[50]->colition_test(bll->b)){
               cout << "PERDISTE\nno debes matar al rehen" <<endl;
               exit(0);
            }
            if(mansion[51]->compare_floor(bll->b)||mansion[51]->colition_test(bll->b)){
               terror3=false;
            }

         }
      }
   }
}


int cont=0;
void Timer(int value){
   if(g_key['w'] || g_key['W']) {
      if (g_shift_down == true) {
            mover('w',g_translation_speed*sigilo);
            //g_camera.Move(g_translation_speed*sigilo);
   }else
      mover('w',g_translation_speed);
      //g_camera.Move(g_translation_speed);
   }
   if(g_key['s'] || g_key['S']) {
      if (g_shift_down == true) {
         mover('s',g_translation_speed*sigilo);
         //g_camera.Move(-g_translation_speed*sigilo);
   }else
      mover('s',g_translation_speed);
         //g_camera.Move(-g_translation_speed);
   }
   if(g_key['a'] || g_key['A']) {
      if (g_shift_down == true) {
         mover('a',g_translation_speed*sigilo);
         //g_camera.Strafe(g_translation_speed*sigilo);
   }else
      mover('a',g_translation_speed);
         //g_camera.Strafe(g_translation_speed);
   }
   if(g_key['d'] || g_key['D']) {
      if (g_shift_down == true) {
         mover('d',g_translation_speed*sigilo);
         //g_camera.Strafe(-g_translation_speed*sigilo);
   }else
      mover('d',g_translation_speed);
         //g_camera.Strafe(-g_translation_speed);
   }
   if(g_key['r'] || g_key['R']) {
      bala_act = 0;
   }
   if(g_key['x']) {
      float x,y,z;
      g_camera.GetPos(x,y,z);
      cout << "x: "<< x <<endl;
      cout << "y: "<< y <<endl;
      cout << "z: "<< z <<endl;
   }
   if(g_mouse_left_down) {
      //recargar
      if(bala_act !=QUANT_BULLETS&&cont%6==0){
         float x,y,z;
         float v[3];
         float inc= 0.2;
         bullet[bala_act]->viva=true;
         g_camera.GetPos(x,y,z);
         g_camera.GetDirectionVector(v[0],v[1],v[2]);
         float r = (float)(rand()%10);
         v[0]=v[0]+r/600*pow(-1,r);
         r = (float)(rand()%10);
         v[1]=v[1]+r/600*pow(-1,r);
         r = (float)(rand()%10);
         v[2]=v[2]+r/600*pow(-1,r);

         bullet[bala_act]->setDir(v[0],v[1],v[2]);
         bullet[bala_act]->b->setPos(x+v[0],y+v[1],z+v[2]);
         try_colition(bullet[bala_act]);
         bala_act= (bala_act +1 );
      }
      cont++;
      //g_camera.Fly(-g_translation_speed*2);
   }
   if (g_mouse_left_down==false){
      cont=0;
   }
   if(g_mouse_right_down) {
     g_camera.Fly(g_translation_speed*2);
   }
   if(terror1==false && terror2 ==false&& terror3 ==false){
      cout << "ganaste salvaste al rehen"<<endl;
      exit(0);
   }
   gravedad();
   t++;
   //cout << "velocidad: "<<v<<endl<< "altura:"<< g_camera.GetY()<<endl;
   glutTimerFunc(1, Timer, 0);
}

void Idle(){
    Display();
}


void Mouse(int button, int state, int x, int y)
{
    if(state == GLUT_DOWN) {
        if(button == GLUT_LEFT_BUTTON) {
            g_mouse_left_down = true;
        }
        else if(button == GLUT_RIGHT_BUTTON) {
            g_mouse_right_down = true;
        }
    }
    else if(state == GLUT_UP) {
        if(button == GLUT_LEFT_BUTTON) {
            g_mouse_left_down = false;
        }
        else if(button == GLUT_RIGHT_BUTTON) {
            g_mouse_right_down = false;
        }
    }
}

void MouseMotion(int x, int y)
{
    // This variable is hack to stop glutWarpPointer from triggering an event callback to Mouse(...)
    // This avoids it being called recursively and hanging up the event loop
    static bool just_warped = false;

    if(just_warped) {
      just_warped = false;
      return;
    }

    int dx = x - g_viewport_width/2;
    int dy =g_viewport_height/2 - y;
    if(dx) {
      g_camera.RotateYaw(g_rotation_speed*dx);
    }
    if(dy) {
      g_camera.RotatePitch(g_rotation_speed*dy);
    }

    glutWarpPointer(g_viewport_width/2, g_viewport_height/2);
    just_warped = true;
}

/*
COLISIONES
*/
void iniciar_colisiones(){
   float x,y,z;
   g_camera.GetPos(x,y,z);
   lpersonaje.agregar(x,y,z,0.5);
   lpersonaje.agregar(x,y-0.5,z,0.5);
   lpersonaje.agregar(x,y-1,z,0.5);
   lpersonaje.agregar(x,y-1.5,z,0.5);

   lsig.agregar(x,y,z,0.5);
   lsig.agregar(x,y-0.5,z,0.5);
   lsig.agregar(x,y-1,z,0.5);
   lsig.agregar(x,y-1.5,z,0.5);
}

void refreshColition(){
   float x,y,z;
   g_camera.GetPos(x,y,z);
   Elemento* act = lsig.inicio;
   act->setPos(x,y,z);
   act = act->sig;
   act->setPos(x,y-0.5,z);
   act = act->sig;
   act->setPos(x,y-1,z);
   act = act->sig;
   act->setPos(x,y-1.5,z);
   //cout << x <<" "<<y<<" "<<z<< endl;

}

void refreshColition(float x, float y, float z){
   Elemento* act = lsig.inicio;
   act->setPos(x,y,z);
   act = act->sig;
   act->setPos(x,y-0.5,z);
   act = act->sig;
   act->setPos(x,y-1,z);
   act = act->sig;
   act->setPos(x,y-1.5,z);

}

void switch_list(Lista l1, Lista l2){
   //l1 = l2
   float x,y,z;
   Elemento* act = l2.inicio;
   Elemento* aux = l1.inicio;
   act->getPos(x,y,z);
   aux->setPos(x,y,z);
   act = act->sig;
   aux = aux->sig;
   act->getPos(x,y,z);
   aux->setPos(x,y,z);
   act = act->sig;
   aux = aux->sig;
   act->getPos(x,y,z);
   aux->setPos(x,y,z);
   act = act->sig;
   aux = aux->sig;
   act->getPos(x,y,z);
   aux->setPos(x,y,z);

}

void mover(char m,float inc){
   float nx,ny,nz;
   refreshColition();
   switch(m){
      case 'w':
      g_camera.getMove(inc,nx,ny,nz);
      refreshColition(nx,ny,nz);
      if(colitionTest()==false){
         g_camera.Move(inc);
         switch_list(lpersonaje,lsig);
      }
      break;
      case 's':
      g_camera.getMove(-inc,nx,ny,nz);
      refreshColition(nx,ny,nz);
      if(colitionTest()==false){
         g_camera.Move(-inc);
         switch_list(lpersonaje,lsig);
      }
      break;
      case 'a':
      g_camera.getStrafe(inc,nx,ny,nz);
      refreshColition(nx,ny,nz);
      if(colitionTest()==false){
         g_camera.Strafe(inc);
         switch_list(lpersonaje,lsig);
      }
      break;
      case 'd':
      g_camera.getStrafe(-inc,nx,ny,nz);
      refreshColition(nx,ny,nz);
      if(colitionTest()==false){
         g_camera.Strafe(-inc);
         switch_list(lpersonaje,lsig);
      }
      break;
   }
}

bool mansion_colition(Lista l){
   int i=0;
   while(mansion[i]!=NULL){
      if(mansion[i]->colition_test(l)){
         return true;
      }
      i++;
   }
   return false;
}

bool mansion_colition(Elemento* e){
   int i=0;
   while(mansion[i]!=NULL){
      if(mansion[i]->colition_test(e)){
         return true;
      }
      i++;
   }
   return false;
}

/*bool test_mansion(Lista l){
   int i=0;
   while(mansion[i] != NULL){
      if(test_g(l,*mansion[i])){
         return true;
      }
      i++;
   }
   return false;
}
*/
bool colitionTest(){
   if(mansion_colition(lsig)||mapa.colition_test(lsig)){
      //cout <<"sep"<<endl;
      return true;
   }
   else{
      //cout << "nop"<<endl;
      return false;
   }
}
