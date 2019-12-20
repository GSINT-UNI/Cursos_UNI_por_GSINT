#include <stdio.h>
#include <GL/glut.h> // Header File For The GLut Library
#include <math.h>

/*  Initialize z-buffer, projection matrix, light source,
 *  and lighting model.  Do not specify a material property here.
 */

int on=1;
GLfloat x=0.0, y=0.0, z=0.0;

void init(void)
{
   GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
   GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat position[] = { 0.0+x, 3.0+y, 2.0+z, 0.0 };
   GLfloat lmodel_ambient[] = { 0.4, 0.4, 0.4, 1.0 };
   GLfloat local_view[] = { 0.0 };

   glClearColor(0.0, 0.1, 0.1, 0.0);
   glEnable(GL_DEPTH_TEST);
   glShadeModel(GL_SMOOTH);

   glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
   glLightfv(GL_LIGHT0, GL_POSITION, position);

   glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);

   glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
   glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);

   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
}

/*  Draw twelve spheres in 3 rows with 4 columns.
 *  The spheres in the first row have materials with no ambient reflection.
 *  The second row has materials with significant ambient reflection.
 *  The third row has materials with colored ambient reflection.
 *
 *  The first column has materials with blue, diffuse reflection only.
 *  The second column has blue diffuse reflection, as well as specular
 *  reflection with a low shininess exponent.
 *  The third column has blue diffuse reflection, as well as specular
 *  reflection with a high shininess exponent (a more concentrated highlight).
 *  The fourth column has materials which also include an emissive component.
 *
 *
 */
 int g_viewport_width = 0;
 int g_viewport_height = 0;


float camera_pos[3]={0,0,10};

void refresh_camera(void){
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(60.0,g_viewport_width/g_viewport_height,0.01,100.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt(camera_pos[0],camera_pos[1],camera_pos[2], 0, 0, 0, 0.0, 1.0, 0.0);

}

void piso(){
   glBegin(GL_QUADS);
   glVertex3f(-5,-3.25,5);
   glVertex3f(5,-3.25,5);
   glVertex3f(5,-3.25,-5);
   glVertex3f(-5,-3.25,-5);
   glEnd();
}

float mov1[3]={0,0,0};
float mov2[3]={0,0,0};
float a = 0.02;
float vel= 0.01;
int fase=1;
float velz=0.1;
float velz2=0.2;
void movimiento(){
   float cont;
   if(mov1[1] >=-4.82999&&fase ==1){//caida
      mov1[0];
      mov1[1]-=(vel+a);
      mov1[2];
      vel = vel + a;
   }else{
      //rebote
      if(fase==1){
         fase=2;
         a = 0.02;
         vel= 0.2;
      }
      if(fase==2 && mov1[1] > -5.20){
         mov1[2]-=velz;
         mov1[1]+=(vel-a);
         vel = vel -a;
         mov2[2]+=velz2;
         velz2-=0.01;
      }else {
         if (fase == 2){
            fase=3;
            cont = 1;//para los reincios
            a = 0.02;
            vel = 0.1;
         }
         if (fase == 3 && velz>0){
            mov1[2] -= velz;
            velz -= 0.005;
            mov1[1]+=vel;
            vel -= a;
            if(mov1[1]<-5.20){//reincio
               vel = 0.1*cont;//nuevo valor de la velocidad a incrementar
               cont*=0.7;
            }
            if(mov1[2]<-4){
               fase=4;
            }
         }
      }
   }
}

bool activado =false;
void Timer(int value){
   if (activado)
      movimiento();
   glutPostRedisplay();
   glutTimerFunc(40, Timer, 0);
}

void display(void)
{
   GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
   GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
   GLfloat mat_ambient_color[] = { 0.9, 0.2, 0.2, 1.0 };
   GLfloat mat_diffuse[] = { 0.1, 0.5, 0.8, 1.0 };
   GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat no_shininess[] = { 0.0 };
   GLfloat low_shininess[] = { 5.0 };
   GLfloat high_shininess[] = { 100.0 };
   GLfloat mat_emission[] = {0.1, 0.3, 0.2, 0.0};

   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   refresh_camera();
   piso();
/*  draw sphere in first row, first column
 *  diffuse reflection only; no ambient or specular
 */
    glPushMatrix();
    glTranslatef (-3.75+mov1[0], 3.0+mov1[1], 0.0+mov1[2]);
    glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
    glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    glutSolidSphere(1.0, 16, 16);
    glPopMatrix();

/*  draw sphere in first row, second column
 *  diffuse and specular reflection; low shininess; no ambient
 */
    glPushMatrix();
    glTranslatef (-1.25, 3.0, 0.0);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
    glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    glutSolidSphere(1.0, 16, 16);
    glPopMatrix();

/*  draw sphere in first row, third column
 *  diffuse and specular reflection; high shininess; no ambient
 */
    glPushMatrix();
    glTranslatef (1.25+mov1[0], 3.0+mov1[1], 0.0+mov1[2]);
    glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    glutSolidSphere(1.0, 16, 16);
    glPopMatrix();

/*  draw sphere in first row, fourth column
 *  diffuse reflection; emission; no ambient or specular reflection
 */
    glPushMatrix();
    glTranslatef (3.75, 3.0, 0.0);
    glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
    glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
    glutSolidSphere(1.0, 16, 16);
    glPopMatrix();

/*  draw sphere in third row, first column
 *  colored ambient and diffuse reflection; no specular
 */
    glPushMatrix();
    glTranslatef (-3.75+mov2[0], -3.0+mov2[1], 0.5+mov2[2]);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
    glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    glutSolidSphere(0.25, 16, 16);
    glPopMatrix();

/*  draw sphere in third row, second column
 *  colored ambient, diffuse and specular reflection; low shininess
 */
    glPushMatrix();
    glTranslatef (-1.25, -3.0, 0.5);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    glutSolidSphere(0.25, 16, 16);
    glPopMatrix();

/*  draw sphere in third row, third column
 *  colored ambient, diffuse and specular reflection; high shininess
 */
    glPushMatrix();
    glTranslatef (1.25+mov2[0], -3.0+mov2[1], 0.5+mov2[2]);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    glutSolidSphere(0.25, 16, 16);
    glPopMatrix();
/*  draw sphere in third row, fourth column
 *  colored ambient and diffuse reflection; emission; no specular
 */
   glPushMatrix();
   glTranslatef (3.75, -3.0, 0.5);
   glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
   glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
   glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
   glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
   glutSolidSphere(0.25, 16, 16);
   glPopMatrix();

   glFlush();
}

void reshape(int w, int h)
{

   g_viewport_width = w;
   g_viewport_height = h;

   glViewport(0, 0, w, h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   /*if (w <= (h * 2))
      glOrtho (-6.0, 6.0, -3.0*((GLfloat)h*2)/(GLfloat)w,
         3.0*((GLfloat)h*2)/(GLfloat)w, -10.0, 10.0);
   else
      glOrtho (-6.0*(GLfloat)w/((GLfloat)h*2),
         6.0*(GLfloat)w/((GLfloat)h*2), -3.0, 3.0, -10.0, 10.0);
   */

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

void keyboard(unsigned char key, int a, int b)
{
   switch (key) {
      case 27:
         exit(0);
         break;
	  case 'l':
	  {
		x+=1.0; init(); glutPostRedisplay();
	  } break;
     case 'j':
	  {
		x-=1.0; init(); glutPostRedisplay();
	  } break;
     case 'i':
	  {
		y+=1.0; init(); glutPostRedisplay();
	  } break;
     case 'k':
	  {
		y-=1.0; init(); glutPostRedisplay();
	  } break;
     case 'u':
	  {
		z-=1.0; init(); glutPostRedisplay();
	  } break;
     case 'h':
	  {
		z+=1.0; init(); glutPostRedisplay();
	  } break;

     case 'd':
	  {
		camera_pos[0]+=1.0; init(); glutPostRedisplay();
	  } break;
     case 'a':
	  {
		camera_pos[0]-=1.0; init(); glutPostRedisplay();
	  } break;
     case 'w':
	  {
		camera_pos[1]+=1.0; init(); glutPostRedisplay();
	  } break;
     case 's':
	  {
		camera_pos[1]-=1.0; init(); glutPostRedisplay();
	  } break;
     case 'r':
	  {
		camera_pos[2]-=1.0; init(); glutPostRedisplay();
	  } break;
     case 'f':
	  {
		camera_pos[2]+=1.0; init(); glutPostRedisplay();
	  } break;
	  case 'o':
		{
			if (on) { glDisable(GL_LIGHT0); on=0; }
			else { glEnable(GL_LIGHT0); on=1; } //in this case I have to refer to init() functio
												// glEnable() doesn't enable specular reflection of material
			glutPostRedisplay();
		} break;
     case ' ':
      activado = true;
   }
}

int main(int argc, char** argv)
{
   printf("Instrucciones:\n");
   printf("la vision se mueve con las teclas awsd para arriba abajo izquierda y derecha\n");
   printf("ademas rf son para avanzar y retroceder\n");
   printf("la luz se mueve con las teclas ijkl para arriba abajo izquierda y derecha\n");
   printf("ademas uh son para que la luz avance y retroceda\n");
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize (600, 450);
   glutCreateWindow(argv[0]);
   init();
   glutReshapeFunc(reshape);
   glutDisplayFunc(display);
   glutKeyboardFunc (keyboard);
   glutTimerFunc(100, Timer, 0);
   glutMainLoop();
   return 0;
}
