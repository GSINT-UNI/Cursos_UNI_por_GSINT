/****
  Adapted from a program by 
  9/9/98 Paul Rademacher (rademach@cs.unc.edu)

****************************************************************************/

#include <string.h>
#include <GL/glut.h>
#include "GL/glui.h"

/** These are the live variables passed into GLUI ***/
int   wireframe = 0;
int   segments = 8;
int   main_window;

/***************************************** myGlutIdle() ***********/

void myGlutIdle( void )
{
  /* According to the GLUT specification, the current window is
     undefined during an idle callback.  So we need to explicitly change
     it if necessary */
  if ( glutGetWindow() != main_window )
    glutSetWindow(main_window);

  glutPostRedisplay();
}

/**************************************** myGlutReshape() *************/

void myGlutReshape( int x, int y )
{
  float xy_aspect;

  xy_aspect = (float)x / (float)y;
  GLUI_Master.auto_set_viewport();

  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  glFrustum( -xy_aspect*.08, xy_aspect*.08, -.08, .08, .1, 15.0 );

  glutPostRedisplay();
}
/**************************************** myGlutReshape() *************/
void setMaterial ( GLfloat ambientR, GLfloat ambientG, GLfloat ambientB, 
		   GLfloat diffuseR, GLfloat diffuseG, GLfloat diffuseB, 
		   GLfloat specularR, GLfloat specularG, GLfloat specularB,
		   GLfloat shininess ) {

    GLfloat ambient[] = { ambientR, ambientG, ambientB };
    GLfloat diffuse[] = { diffuseR, diffuseG, diffuseB };
    GLfloat specular[] = { specularR, specularG, specularB };

    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,ambient);
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,diffuse);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,specular);
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shininess);
}




/***************************************** myGlutDisplay() *****************/

void myGlutDisplay( void )
{
  static float rotationX = 0.0, rotationY = 0.0;

  glClearColor( .9f, .5f, .5f, 1.0f );
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  /*** Rotate the object ***/
  rotationX += 3.3f;
  rotationY += 4.7f;

  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();
  glTranslatef( 0.0, 0.0, -1.0 );
  glRotatef( rotationY, 0.0, 1.0, 0.0 );
  glRotatef( rotationX, 1.0, 0.0, 0.0 );

  /*** Now we render object, using the variables 'segments' and
    'wireframe'.  These are _live_ variables, which are transparently
    updated by GLUI ***/


  //setMaterial(0.0,0.5,1.0,0.0,0.5,1.0,1.0,1.0,1.0,1);
  setMaterial(1.0,0.0,0.0,1.0,1.0,0.0,1.0,0.0,0.0,50);
  if ( wireframe )
    glutWireTorus( .2,.5,16,segments );
  else
    glutSolidTorus( .2,.5,16,segments );

  glutSwapBuffers();
}

/**************************************** main() ********************/

int main(int argc, char* argv[])
{
  /****************************************/
  /*   Initialize GLUT and create window  */
  /****************************************/
  glutInit(&argc, argv);
  glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );
  glutInitWindowPosition( 50, 50 );
  glutInitWindowSize( 300, 300 );

  main_window = glutCreateWindow( "GLUI Example 1" );
  glutDisplayFunc( myGlutDisplay );
  glutReshapeFunc( myGlutReshape );

  /****************************************/
  /*       Set up OpenGL lights           */
  /****************************************/

  GLfloat light0_ambient[] =  {0.1f, 0.1f, 0.3f, 1.0f};
  GLfloat light0_diffuse[] =  {.6f, .6f, 1.0f, 1.0f};
  GLfloat light0_position[] = {1.0f, 1.0f, 1.0f, 0.0f};

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
  glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

  /****************************************/
  /*          Enable z-buffering          */
  /****************************************/

  glEnable(GL_DEPTH_TEST);

  /****************************************/
  /*         Here's the GLUI code         */
  /****************************************/

  GLUI *glui = GLUI_Master.create_glui_subwindow(main_window,
                     GLUI_SUBWINDOW_TOP);

  glui->add_checkbox( "Wireframe", &wireframe );
  GLUI_Spinner *segment_spinner =
    glui->add_spinner( "Segments:", GLUI_SPINNER_INT, &segments );
  segment_spinner->set_int_limits( 3, 60 );

  glui->set_main_gfx_window( main_window );
  GLUI_Listbox *listbox = glui->add_listbox("A listbox");
  listbox->add_item(1,"Red");
  listbox->add_item(2,"Green");
  listbox->add_item(3,"Blue");

  glui->add_statictext("Example 2");
  glui->add_separator();
  GLUI_Panel *obj_panel = glui->add_panel ("Test Panel");
  glui->add_button("Quit",0,(GLUI_Update_CB)exit);
  GLUI_RadioGroup *group1 = glui->add_radiogroup_to_panel(obj_panel);
  glui->add_radiobutton_to_group(group1,"Option 1");
  glui->add_radiobutton_to_group(group1,"Option 2");
  GLUI_Rotation *arcball = glui->add_rotation("ball (doesn't do anything)");
  
  /* We register the idle callback with GLUI, *not* with GLUT */
  GLUI_Master.set_glutIdleFunc( myGlutIdle );
  GLUI_Master.set_glutReshapeFunc( myGlutReshape );
  glutMainLoop();
}
