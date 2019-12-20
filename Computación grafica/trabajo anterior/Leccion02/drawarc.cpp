/* -- INCLUDE FILES ------------------------------------------------------ */

#include <GL/glut.h>
#define _USE_MATH_DEFINES 
#include <math.h>

/* -- DATA STRUCTURES ---------------------------------------------------- */
// Our point class.
class GLintPoint  {

};

/* -- GLOBAL VARIABLES --------------------------------------------------- */

/* -- LOCAL VARIABLES ---------------------------------------------------- */


/* ----------------------------------------------------------------------- 

/* ----------------------------------------------------------------------- */
/* Function    : void myInit( void )
 *
 * Description : Initialize OpenGL and the window where things will be
 *               drawn.
 *
 * Parameters  : void
 *
 * Returns     : void
 */

void myInit( void )  {
  glClearColor( 1.0, 1.0, 1.0, 0.0 );
  glColor3f( 0.0, 0.0, 0.0 );
  glPointSize( 1.0 );
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity( );
  gluOrtho2D( 0.0, 640.0, 0.0, 480.0 );
}

/* ----------------------------------------------------------------------- */
/* Function    : void drawArc(  )
 *
 * Description : Dibuja un arco.
 *
 * Parameters  : float x, float y, float r, float t0, float sweep
 *
 * Returns     : void
 */

void drawArc(float x, float y, float r,float t0, float sweep)
{
	float t, dt; /* angulo */
	
	int n = 30; /* # de segmentos */
	
	int	i;
	t = t0 * M_PI/180.0; /* radianes */
	
	dt = sweep * M_PI/(180*n); /* incremento */
	glBegin(GL_LINE_STRIP);
	for(i=0; i<=n; i++, t += dt)
		glVertex2f(x + r*cos(t), y + r*sin(t));
	glEnd();
	glFlush(); //Presenta el dibujo en la pantalla
}

/* ----------------------------------------------------------------------- */
/* Function    : void myDisplay( void )
 *
 * Description : This function gets called everytime the window needs to
 *               be redrawn.
 *
 * Parameters  : void
 *
 * Returns     : void
 */

void myDisplay( void )  {
  glClear( GL_COLOR_BUFFER_BIT );
  drawArc( 100.0, 100.0, 100.0,45.0, 360.0);
}


/* ----------------------------------------------------------------------- */
/* Function    : int main( int argc, char** argv )
 *
 * Description : This is the main function. It sets up the rendering
 *               context, and then reacts to user events.
 *
 * Parameters  : int argc     : Number of command-line arguments.
 *               char *argv[] : Array of command-line arguments.
 *
 * Returns     : int : Return code to pass to the shell.
 */

int main( int argc, char *argv[] )  {
  // Inicializar GLUT.
  glutInit( &argc, argv );
  // Definir Color RGB y Single Buffer.
  glutInitDisplayMode( GLUT_SINGLE | GLUT_RGB );
  // Definir la ventana en pixeles de la pantalla .
  glutInitWindowSize( 640, 480 );
  // Definir la posicion de la ventanaen pixeles de la pantalla.
  glutInitWindowPosition( 100, 150 );
  // Crear la ventana.
  glutCreateWindow( "drawArc" );
  // Definir la funcion de callback que usaremos para dibujar algo.
  glutDisplayFunc( myDisplay );
  // Inicializar algunas cosas.
  myInit( );
  // Ahora que tenemos todo definido, el loop  que responde  a eventos.
  glutMainLoop( );
}

/* ----------------------------------------------------------------------- */
