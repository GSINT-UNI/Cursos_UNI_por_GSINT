
#include <math.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "glui.h"

#include "tga.h"
#include "terrain.h"





// stuff for lighting
GLfloat lAmbient[] = {0.2,0.2,0.2,1.0};
GLfloat lDiffuse[] = {1.0,1.0,1.0,1.0};
GLfloat lSpecular[] = {1.0,1.0,1.0,1.0};

GLfloat lPosition[] = {0.0, 100.0, 0.0, 0.0};

// materials
GLfloat mSpecular[] = {0.0,0.0,0.0,0.0};
// the smaller the larger the specular area is
GLfloat mShininess[] = {128.0};

//colors
GLfloat cBlack[] = {0.0,0.0,0.0,1.0};
GLfloat cOrange[] = {1.0,0.5,0.5,1.0}; 
GLfloat cWhite[] = {1.0,1.0,1.0,1.0}; 
GLfloat cGrey[] = {0.1,0.1,0.1,1.0};
GLfloat cLightGrey[] = {0.9,0.9,0.9,1.0};

int lighting=0,simulateLighting = 0;

#define	EXAMINE				1
#define	WALKFLY				2
int navigationMode = EXAMINE;
int accelerate = 0;


float angle=0.0,deltaAngle = 0.0,ratio;
float x=0.0f,y=1.75f,z=5.0f;
float lx=0.0f,ly=0.0f,lz=-1.0f,deltaMove=0.0;
int h,w;
int font=(int)GLUT_BITMAP_8_BY_13;
static GLint snowman_display_list;
int bitmapHeight=13;
int mode;
float angle2,angle2Y,angleY;
static int deltaX=-1000,deltaY;

int terrainDL,iterationsDone = 0,totalIterations = 0;
char s[100];

int frame,time,timebase=0;
char currentMode[100];

// this string keeps the last good setting 
// for the game mode
char gameModeString[40] = "640x480";

char filename[150] = "";
int mainWindow;
int faceType = GL_TRIANGLE_STRIP;
int normals=0;
float min = 0.0;
float max = 20.0;
int terrainw=128,terrainl=128,terrainMode = 0,terrainFace = 0;
int iterate=0;
int imageNumber = 0;
int show=1;
float waterHeight = 0.8;
int waterShow = 0;

float filter[25] = {
		0.0, 0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0, 0.0,
		0.0, 0.0, 0.0, 0.0, 0.0};

float filterAverage[25] = {
		0.0,	0.0,	0.0,	0.0,	0.0,
		0.0,	1.0,	1.0,	1.0,	0.0,
		0.0,	1.0,	1.0,	1.0,	0.0,
		0.0,	1.0,	1.0,	1.0,	0.0,
		0.0,	0.0,	0.0,	0.0,	0.0};

		
float filterBlur4[25] = {
		0.0,	0.0,	0.0,	0.0,	0.0,
		0.0,	0.0,	0.125,	0.0,	0.0,
		0.0,	0.125,	0.5,	0.125,	0.0,
		0.0,	0.0,	0.125,	0.0,	0.0,
		0.0,	0.0,	0.0,	0.0,	0.0};


float filterBlur8[25] = {
		0.0,	0.0,	0.0,	0.0,	0.0,
		0.0,	0.0625,	0.0625,	0.0625,	0.0,
		0.0,	0.0625,	0.5,	0.0625,	0.0,
		0.0,	0.0625,	0.0625,	0.0625,	0.0,
		0.0,	0.0,	0.0,	0.0,	0.0};

float filterStrongBlur[25] = {
		1.0,	1.0,	1.0,	1.0,	1.0,
		1.0,	2.0,	2.0,	2.0,	1.0,
		1.0,	2.0,	4.0,	2.0,	1.0,
		1.0,	2.0,	2.0,	2.0,	1.0,
		1.0,	1.0,	1.0,	1.0,	1.0};


/* GLUI definitions and variables */

GLUI *glui,*glui_bottom,*glui_filter;
GLUI_EditText *glui_filename;
GLUI_RadioGroup *radioLight,*radioTerrain,*radioMode,*radioFace;
GLUI_EditText *glui_fps,*glui_terrainw,*glui_terrainl;
GLUI_Panel *glui_panel1,*glui_terrainGeneration, *glui_water,*glui_filterOptions;
GLUI_Panel *glui_panel3,*glui_faultPanel,*glui_iterate, *glui_stepsPanel;
GLUI_Panel *glui_heights,*glui_terrain,*glui_surface, *glui_smoothPanel;
GLUI_EditText *glui_minHeight,*glui_itDone;
GLUI_EditText *glui_maxHeight,*glui_roughness;
GLUI_Button *glui_applyHeights,*glui_generate,*glui_b1,*glui_b2,*glui_b3;
GLUI_RadioButton *glui_rb1,*glui_rb2,*glui_rb3,*glui_rb4,*glui_rb5,*glui_rb6,*glui_rb7;
GLUI_Checkbox *glui_normals,*glui_show, *glui_waterShow;
GLUI_Listbox *glui_algorithmLB,*glui_faceModeLB,*glui_faceLB,*glui_lightLB,*glui_navModeLB;
GLUI_Rotation *glui_rotate;
GLUI_Translation *glui_transXY,*glui_transX,*glui_transY,*glui_transZ;
GLUI_EditText *glui_maxDisp,*glui_minDisp,*glui_interval,*glui_waveSize, 
	*glui_circleSize;
GLUI_Spinner *glui_rs,*glui_iterations, *glui_steps, *glui_waterHeight, *glui_smooth;
GLUI_Checkbox *glui_particleMode;
GLUI_Rollout *glui_mainOptions;

GLUI_EditText  *(*glui_f);
GLUI_Panel *glui_filterOptions1;
GLUI_Listbox *glui_filters;


#define FILENAME_ID			100
#define LIGHT_ID			101
#define GRAB_ID				102
#define MAXHEIGHT_ID		103
#define MINHEIGHT_ID		104
#define RESETHEIGHTS_ID		105
#define RADIOTERRAIN_ID		106
#define NORMALS_ID			107
#define	TERRAINWIDTH_ID		108
#define TERRAINLENGTH_ID	109
#define FACEMODE_ID			110
#define FACE_ID				111
#define APPLYHEIGHTS_ID		112
#define ALGORITHM_ID		113
#define	GENERATE_ID			114
#define WIREFRAME_ID		116
#define SOLID_ID			117
#define ITERATIONS_ID		118
#define	STOP_ID				119
#define	START_ID			120
#define TOTALIT_ID			121
#define NAVIGATION_ID		122
#define RANDOM_ID			123
#define MAXDISP_ID			124
#define MINDISP_ID			125
#define WAVESIZE_ID			126
#define INTERVAL_ID			127
#define SAVETGA_ID			128
#define SHOW_ID				129
#define CIRCLESIZE_ID		130
#define ROUGHNESS_ID		131
#define STEPS_ID			132
#define GO_ID				133
#define WATERSHOW_ID		134
#define WATERHEIGHT_ID		135
#define SMOOTH_ID			136
#define PARTICLEMODE_ID		137

#define F11_ID				138
#define FILTER_ID			139
#define APPLYFILTER_ID		140
#define	CLOSEFILTER_ID		141
#define	OPENFILTER_ID		142



#define FilterId			1
#define FilterAverage		2
#define FilterBlur4			3
#define FilterBlur8			4
#define FilterStrongBlur	5


float m[16];
float trans[3] = {0.0,0.0,0.0};
/* code */


void init();



void glui_filterControl( int control ) {

	float *f;
	int aux,i;

	switch(control) {

		case APPLYFILTER_ID:
			f = (float *)malloc(sizeof(float) * 25);
			for(i=0;i<25;i++)
				f[i] = glui_f[i]->get_float_val();
			terrainSetFilter(f);
			free(f);
			terrainApplyFilter();
			glDeleteLists(terrainDL,1);
			terrainDL = terrainCreateDL(lighting,faceType);
			break;

		case FILTER_ID:
			aux = glui_filters->get_int_val();
			switch(aux) {
				case FilterId: f = filter;break;
				case FilterAverage: f = filterAverage;break;
				case FilterBlur4: f = filterBlur4;break;
				case FilterBlur8: f = filterBlur8;break;
				case FilterStrongBlur: f = filterStrongBlur;break;
			}
			for(i=0;i<25;i++)
				glui_f[i]->set_float_val(f[i]);
			break;
		case CLOSEFILTER_ID:
			glui_filter->hide();
			break;
		case OPENFILTER_ID:
			glui_filter->show();
			break;
	}

}

void glui_control( int control )
{
	int status;
	int tx, ty, tw, th;
	float b;
	int aux;

	switch(control) {
		case FILENAME_ID:
			strcpy(filename,glui_filename->get_text());
			status = terrainLoadFromImage(filename,1);
			if (!status) {
				glDeleteLists(terrainDL,1);
				terrainScaleHeights(min,max);
				terrainDL = terrainCreateDL(lighting,GL_TRIANGLE_STRIP);
				terrainl = terrainGetLength();
				terrainw = terrainGetWidth();
				glui_terrainl->set_int_val(terrainl);
				glui_terrainw->set_int_val(terrainw);
				y = terrainGetHeight(0,0) + 1.75;
				x=0;z=0;
			}
			break;
		case LIGHT_ID:
			if (glui_lightLB->get_int_val() == 0) {
				lighting = 1;
				simulateLighting = 0;
			}
			else if (glui_lightLB->get_int_val() == 1) {
				lighting = 0;
				simulateLighting = 1;
			}
			else {
				lighting = 0;
				simulateLighting = 0;
			}
			terrainSimulateLighting(simulateLighting);
			glDeleteLists(terrainDL,1);
			if (lighting) {
				glEnable(GL_LIGHTING);
				glEnable(GL_LIGHT0);
			}
			else {
				glDisable(GL_LIGHT0);
				glDisable(GL_LIGHTING);
			}
			terrainSetNormals(normals);
			terrainDL = terrainCreateDL(lighting,faceType);

			break;
		case GRAB_ID:
			GLUI_Master.get_viewport_area( &tx, &ty, &tw, &th );
			tgaGrabScreenSeries("3dtechscreen",tx,ty,tw,th);
			break;
		case MAXHEIGHT_ID:
		case MINHEIGHT_ID:
			min = glui_minHeight->get_float_val();
			max = glui_maxHeight->get_float_val();
			if (min == max)
				glui_applyHeights->disable();
			else
				glui_applyHeights->enable();
			break;
		case APPLYHEIGHTS_ID:
			terrainScaleHeights(min,max);
			glDeleteLists(terrainDL,1);
			terrainDL = terrainCreateDL(lighting,faceType);
			if (y < terrainGetHeight((int)x,(int)z))
				y = terrainGetHeight((int)x,(int)z) + 1.75;
			break;
		case RESETHEIGHTS_ID:
			max = 20.0;
			min = 0.0;
			glui_minHeight->set_float_val(min);
			glui_maxHeight->set_float_val(max);
			terrainScaleHeights(min,max);
			glDeleteLists(terrainDL,1);
			terrainDL = terrainCreateDL(lighting,faceType);
			y = terrainGetHeight((int)x,(int)z) + 1.75;
			break;
		case NORMALS_ID:
			normals = glui_normals->get_int_val();
			terrainSetNormals(normals);
			glDeleteLists(terrainDL,1);
			terrainDL = terrainCreateDL(lighting,faceType);
			break;
		case FACE_ID:
			faceType = glui_faceLB->get_int_val();
			glDeleteLists(terrainDL,1);
			terrainDL = terrainCreateDL(lighting,faceType);
			break;
		case FACEMODE_ID:
			if (glui_faceModeLB->get_int_val() == WIREFRAME_ID)
				terrainMode = 0;
			else
				terrainMode = 1;
			break;
		case TERRAINWIDTH_ID:
			break;
		case TERRAINLENGTH_ID:
			break;
		case GENERATE_ID:
			terrainl = glui_terrainl->get_int_val();
			terrainw = glui_terrainw->get_int_val();
			glDeleteLists(terrainDL,1);
			terrainInit(terrainw,terrainl);
			terrainSetNormals(normals);
			terrainDL = terrainCreateDL(lighting,faceType);
			iterationsDone = 0;
			glui_itDone->set_int_val(0);
			totalIterations = 0;
			terrainSetRandomSeed(glui_rs->get_int_val());
			iterate = 0;
			break;

		case ALGORITHM_ID:
			switch (glui_algorithmLB->get_int_val()) {
				case  STEP:
					glui_faultPanel->enable();
					glui_waveSize->disable();
					glui_circleSize->disable();
					glui_stepsPanel->disable();
					glui_itDone->disable();
					glui_particleMode->disable();
					break;
				case RandomDirection:
					glui_faultPanel->enable();
					glui_minDisp->disable();
					glui_interval->disable();
					glui_waveSize->disable();
					glui_circleSize->disable();
					glui_particleMode->enable();
					glui_itDone->disable();
					glui_stepsPanel->disable();
					break;
				case CIRCLE:
					glui_faultPanel->enable();
					glui_waveSize->disable();
					glui_itDone->disable();
					glui_particleMode->disable();
					glui_stepsPanel->disable();
					break;
				case SIN:
				case COS:
					glui_faultPanel->enable();
					glui_circleSize->disable();
					glui_itDone->disable();
					glui_particleMode->disable();
					glui_stepsPanel->disable();
					break;
				case MPD:
					glui_faultPanel->disable();
					glui_stepsPanel->enable();
					break;
			}

			terrainSetFunction(glui_algorithmLB->get_int_val());
			break;
		case RANDOM_ID:
			terrainSetRandomSeed(glui_rs->get_int_val());
			break;
		case MAXDISP_ID:
			terrainSetMaxDisp(glui_maxDisp->get_float_val());
			break;
		case MINDISP_ID:
			terrainSetMinDisp(glui_minDisp->get_float_val());
			break;
		case INTERVAL_ID:
			terrainSetItMinDisp(glui_interval->get_int_val());
			break;
		case WAVESIZE_ID:
			terrainSetWaveSize(glui_waveSize->get_float_val());
			break;
		case CIRCLESIZE_ID:
			terrainSetCircleSize(glui_circleSize->get_float_val());
			break;
		case ROUGHNESS_ID:
			terrainSetRoughness(glui_roughness->get_float_val());
			break;

		case PARTICLEMODE_ID:
			status = glui_particleMode->get_int_val();
			terrainSetParticleMode(status);
			break;
		case ITERATIONS_ID:
			break;
		case SHOW_ID:
			show = glui_show->get_int_val();
			break;
		case START_ID:
			totalIterations += glui_iterations->get_int_val();
			if (iterationsDone == 0)
				terrainSetRandomSeed(glui_rs->get_int_val());
			if (!show) {
				terrainIterate(totalIterations - iterationsDone);
				glDeleteLists(terrainDL,1);
				terrainSetNormals(normals);
				terrainDL = terrainCreateDL(lighting,faceType);
				iterationsDone = totalIterations;
				glui_itDone->set_int_val(iterationsDone);
			}
			iterate = 1;
			break;
				
		case STOP_ID:
			iterate = 0;
			break;

		case GO_ID:
			terrainIterate(glui_steps->get_int_val());
			terrainScaleHeights(0.0,20.0);
			glDeleteLists(terrainDL,1);
			terrainSetNormals(normals);
			b = glui_steps->get_int_val();
			aux = (int)pow(2,b);
			terrainw = (256/aux) * (aux+2);
			terrainl = (256/aux) * (aux+2);
			glui_terrainw->set_int_val(aux+1);
			glui_terrainl->set_int_val(aux+1);
			terrainSetScaleXZ(256/pow(2,b),256/pow(2,b));
			terrainDL = terrainCreateDL(lighting,faceType);
			break;

		case SMOOTH_ID:
			terrainSmooth(glui_smooth->get_float_val());
			glDeleteLists(terrainDL,1);
			terrainDL = terrainCreateDL(lighting,faceType);
			break;

		case NAVIGATION_ID:
			navigationMode = glui_navModeLB->get_int_val();
			if (navigationMode == WALKFLY) {
				if (y < terrainGetHeight((int)x,(int)z))
					y = terrainGetHeight((int)x,(int)z) + 1.75;
				glui_transXY->disable();
				glui_transX->disable();
				glui_transY->disable();
				glui_transZ->disable();
				glui_rotate->disable();
			}
			else {
				glui_transXY->enable();
				glui_transX->enable();
				glui_transY->enable();
				glui_transZ->enable();
				glui_rotate->enable();
			}
			break;
		case SAVETGA_ID:
			terrainSaveAsTGA("3dtech");
			break;
		case WATERSHOW_ID:
			waterShow = glui_waterShow->get_int_val();
			break;
		case WATERHEIGHT_ID:
			waterHeight = glui_waterHeight->get_float_val();
			break;
	}

}


void changeSize(int w1, int h1)
	{

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).

	int tx, ty, tw, th;
	GLUI_Master.get_viewport_area( &tx, &ty, &tw, &th );
	
	h = tw;
	w = tw;
	if(h == 0)
		h = 1;

	ratio = 1.0f * w / h;
	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	// Set the viewport to be the entire window
	GLUI_Master.auto_set_viewport();
//    glViewport(0, 0, w, h);

	// Set the clipping volume
	gluPerspective(45,ratio,0.1,1000);

	// setting the camera now
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(x, y, z, 
		      x + lx,y + ly,z + lz,
			  0.0f,1.0f,0.0f);
}


void initScene() {

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
//	terrainSimulateLighting(simulateLighting);
	terrainDiffuseColor(0.6, 0.8, 0.6);
	terrainAmbientColor(0.04, 0.04, 0.04);
	terrainLightPosition(lPosition[0],lPosition[1],lPosition[2],lPosition[3]);
	terrainDL = terrainCreateDL(lighting,faceType);
	y = terrainGetHeight(0,0) + 1.75;
	
	glLightfv(GL_LIGHT0,GL_AMBIENT,lAmbient);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,lDiffuse);
//	glEnable(GL_LIGHTING);
//	glEnable(GL_LIGHT0);
}

void orientMe(float ang) {

	lx = cos(angle2Y) * sin(ang);
	lz = - cos(angle2Y) * cos(ang);
}


void moveMeFlat(float i) {

	x = x + i*lx;
	z = z + i*lz;
	y = y + i*ly;
}


void renderScene(void) {

	float fps;
	char sfps[10];

	if ( glutGetWindow() != mainWindow ) 
		glutSetWindow(mainWindow);  

	if ((totalIterations > iterationsDone) && (iterate)){
		glDeleteLists(terrainDL,1);
		terrainIterate(1);
		terrainDL = terrainCreateDL(lighting,faceType);
		iterationsDone++;
		glui_itDone->set_int_val(iterationsDone);
	}
	else if (totalIterations == iterationsDone)
		iterate = 0;


	glLoadIdentity();
	if (navigationMode == WALKFLY) {
		if (deltaMove)
			moveMeFlat(deltaMove);
		if (deltaAngle) {
			angle += deltaAngle;
			orientMe(angle);
		}
		gluLookAt(x, y, z, 
				  x + 10*lx,y + 10*ly,z + 10*lz,
				  0.0f,1.0f,0.0f);
	}
	else {
		gluLookAt(0,100,100,0,0,0,0,1,0);
		glTranslatef(trans[0],trans[1],trans[2]);
		glMultMatrixf(m);
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (lighting)
		glLightfv(GL_LIGHT0,GL_POSITION,lPosition);


	glMaterialfv(GL_FRONT, GL_SPECULAR, mSpecular);
	glMaterialfv(GL_FRONT, GL_SHININESS,mShininess);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, cWhite);
	if (lighting) {
		glColorMaterial(GL_FRONT, GL_DIFFUSE);
		glEnable(GL_COLOR_MATERIAL);
	}
	else
		glDisable(GL_COLOR_MATERIAL);

	glColor3f(0.6,0.8,0.6);
	if (terrainMode == 0)
		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

	glCallList(terrainDL);
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

	if (waterShow) {
		glColor3f(0.3,0.3,1);
		glBegin(GL_QUADS);
			glVertex3f(terrainw/2,waterHeight,-terrainl/2);
			glVertex3f(-terrainw/2,waterHeight,-terrainl/2);
			glVertex3f(-terrainw/2,waterHeight,terrainl/2);
			glVertex3f(terrainw/2,waterHeight,terrainl/2);
		glEnd();
	}

	frame++;
	time=glutGet(GLUT_ELAPSED_TIME);
	if (time - timebase > 1000) {
		fps = frame*1000.0/(time-timebase);
		sprintf(sfps,"%5.2f",fps);
		glui_fps->set_text(sfps);
		timebase = time;		
		frame = 0;
	}
	glutSwapBuffers();
}

void quit(int status) {
	terrainDestroy();
	exit(status);
}

void processNormalKeys(unsigned char key, int x, int y) {

	if (key == 27) {
		quit(0);
	}
}


void pressKey(int key, int x, int y)
 {

	switch (key) {
		case GLUT_KEY_LEFT : deltaAngle = -0.005f;break;
		case GLUT_KEY_RIGHT : deltaAngle = 0.005f;break;
		case GLUT_KEY_UP : 
			if (accelerate)
				deltaMove = 1;
			else
				deltaMove = 0.1;
			break;
		case GLUT_KEY_DOWN : 			
			if (accelerate)
				deltaMove = -1;
			else
				deltaMove = -0.1;
			break;
	}
}

void releaseKey(int key, int x, int y) {

	switch (key) {
		case GLUT_KEY_LEFT : if (deltaAngle < 0.0f) 
								 deltaAngle = 0.0f;
							 break;
		case GLUT_KEY_RIGHT : if (deltaAngle > 0.0f) 
								 deltaAngle = 0.0f;
							 break;
		case GLUT_KEY_UP :	 if (deltaMove > 0) 
								 deltaMove = 0;
							 break;
		case GLUT_KEY_DOWN : if (deltaMove < 0) 
								 deltaMove = 0;
							 break;
	}
}


void activeMouseMotion(int x, int y) {

	if (navigationMode == WALKFLY) {
		angle2 = angle + (x-deltaX)*0.001;
		angle2Y = angleY + (y-deltaY) * 0.001;
		if (angle2Y > 1.57)
			angle2Y = 1.57;
		else if (angle2Y < -1.57)
			angle2Y = -1.57;
		lx = cos(angle2Y)*sin(angle2);
		lz = -cos(angle2Y)*cos(angle2);
		ly = -sin(angle2Y);
	}
}


void mousePress(int button, int state, int x, int y) {

	if (state == GLUT_DOWN) {
//		angle2 = 0;
		deltaX = x;
		deltaY = y;
//		angle2Y = 0;
		accelerate=1;
	} 
	else if (state == GLUT_UP) {
		angleY = angle2Y;
		angle = angle2;
		accelerate=0;
	}
}





void init() {
	glutIgnoreKeyRepeat(1);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(pressKey);
	glutSpecialUpFunc(releaseKey);
	glutMotionFunc(activeMouseMotion);
	glutMouseFunc(mousePress);
	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	glutReshapeFunc(changeSize);
	initScene();

}

int main(int argc, char **argv)
{

	int i;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,500);
	mainWindow = glutCreateWindow("Terrain Generator @ 3D-Tech");

	GLUI_Master.set_glutReshapeFunc( changeSize );
	GLUI_Master.set_glutKeyboardFunc( processNormalKeys );
	GLUI_Master.set_glutSpecialFunc( pressKey );
	GLUI_Master.set_glutMouseFunc( mousePress );
	GLUI_Master.set_glutIdleFunc(renderScene);
	GLUI_Master.set_glutDisplayFunc(renderScene);

	glutIgnoreKeyRepeat(1);
	glutSpecialUpFunc(releaseKey);
	glutMotionFunc(activeMouseMotion);




//	glui = GLUI_Master.create_glui_subwindow( mainWindow,
//					    GLUI_SUBWINDOW_RIGHT );
    glui = GLUI_Master.create_glui("Terrain Module",0,515,0);


	glui_terrain = glui->add_panel("Terrain");
	glui_filename = glui->add_edittext_to_panel(glui_terrain, "Image:",
					  GLUI_EDITTEXT_TEXT, NULL,
					  FILENAME_ID, glui_control);
	glui_filename -> set_w( 150 );

	glui_terrainGeneration = glui->add_panel_to_panel(glui_terrain,"Gen. Params");
	glui_terrainw = glui->add_edittext_to_panel(glui_terrainGeneration,"Width",
					GLUI_EDITTEXT_INT, NULL,
					TERRAINWIDTH_ID,glui_control);
	glui_terrainl = glui->add_edittext_to_panel(glui_terrainGeneration,"Length",
					GLUI_EDITTEXT_INT, NULL,
					TERRAINLENGTH_ID,glui_control);
	glui_terrainw->set_int_val(terrainw);
	glui_terrainl->set_int_val(terrainl);


	glui_generate = glui->add_button_to_panel(glui_terrainGeneration,"Generate",GENERATE_ID,glui_control);

//	glui->add_statictext("");

	glui_surface=glui->add_panel("Surface");
	glui_faceLB = glui->add_listbox_to_panel(glui_surface,"Type:",
					NULL,FACE_ID,glui_control);

	glui_faceLB->add_item( GL_TRIANGLE_STRIP, "Triangles" );
	glui_faceLB->add_item( GL_QUAD_STRIP, "Quads" );

	glui_faceModeLB = glui->add_listbox_to_panel(glui_surface,"Mode:",
					NULL,FACEMODE_ID,glui_control);

	glui_faceModeLB->add_item( WIREFRAME_ID, "Wire Frame" );
	glui_faceModeLB->add_item( SOLID_ID, "Solid" );

	glui_lightLB = glui->add_listbox_to_panel(glui_surface,"Lighting:",
								NULL,LIGHT_ID,glui_control);
	glui_lightLB->add_item( 0, "OpenGL" );
	glui_lightLB->add_item( 1, "Simulate" );
	glui_lightLB->add_item( 2, "Off" );
	glui_lightLB->set_int_val(2);

	glui_normals = glui->add_checkbox_to_panel(glui_surface,"Normals",
						NULL,NORMALS_ID,glui_control);
	glui_normals->set_int_val(0);
	
	//	glui->add_statictext("");

	glui_heights = glui->add_panel("Scale Heights");
	glui_minHeight = glui->add_edittext_to_panel(glui_heights, "From : ",
					  GLUI_EDITTEXT_FLOAT, NULL,
					  MINHEIGHT_ID, glui_control );
	glui_maxHeight = glui->add_edittext_to_panel(glui_heights, "To : ",
					  GLUI_EDITTEXT_FLOAT, NULL,
					  MAXHEIGHT_ID, glui_control );
	glui_minHeight->set_float_val(min);
	glui_maxHeight->set_float_val(max);
	glui_applyHeights = glui->add_button_to_panel(glui_heights,"Apply",APPLYHEIGHTS_ID,glui_control);
	glui_b1 = glui->add_button_to_panel(glui_heights,"Reset (0-20)",RESETHEIGHTS_ID,glui_control);
//	glui->add_statictext("");

	glui_water = glui->add_panel("Water Plane");
	glui_waterShow = glui->add_checkbox_to_panel(glui_water, "Show",
						NULL,WATERSHOW_ID,glui_control);
	glui_waterHeight = glui->add_spinner_to_panel(glui_water, "Height: ",
					  GLUI_EDITTEXT_FLOAT, NULL,
					  WATERHEIGHT_ID, glui_control );
	glui_waterHeight->set_float_val(0.8);



	glui_fps = glui->add_edittext("FPS : ",
					  GLUI_EDITTEXT_TEXT, NULL,
					  0, glui_control );	
        glui_fps->disable();

	glui->add_button("Screen Shot", GRAB_ID, glui_control );
	glui->add_button("Save as TGA", SAVETGA_ID,glui_control );



	glui->add_column(true);
	glui_iterate = glui->add_panel("Iterate",true);
	glui_algorithmLB = glui->add_listbox_to_panel(glui_iterate,"Function:",
					NULL,ALGORITHM_ID,glui_control);

	glui_algorithmLB->add_item(MPD,"Midpoint Disp.");
	glui_algorithmLB->add_item(RandomDirection,"Particle Deposition");
	glui_algorithmLB->add_item(STEP,"Fault-Step");
	glui_algorithmLB->add_item(COS,"Fault-Cosine");
	glui_algorithmLB->add_item(SIN,"Fault-Sine");
	glui_algorithmLB->add_item(CIRCLE,"Circles");

	glui_rs = glui->add_spinner_to_panel(glui_iterate,"Random Seed:",
					GLUI_EDITTEXT_INT,NULL,RANDOM_ID,glui_control);
	glui_rs->set_speed(0.00000001);
	glui_rs->set_int_limits(0,100000,GLUI_LIMIT_CLAMP);

	glui_maxDisp = glui->add_edittext_to_panel(glui_iterate,"Max. Disp.:",
					GLUI_EDITTEXT_FLOAT,NULL,MAXDISP_ID,glui_control);
	glui_maxDisp->set_float_val(1.0);

	glui_faultPanel = glui->add_panel_to_panel(glui_iterate,"Fault, Circles");

	glui_minDisp = glui->add_edittext_to_panel(glui_faultPanel,"Min. Disp.:",
					GLUI_EDITTEXT_FLOAT,NULL,MINDISP_ID,glui_control);
	glui_minDisp->set_float_val(0.1);
	glui_minDisp->disable();

	glui_interval = glui->add_edittext_to_panel(glui_faultPanel,"Interval:",
					GLUI_EDITTEXT_INT,NULL,INTERVAL_ID,glui_control);
	glui_interval->set_float_val(100);
	glui_interval->disable();

	glui_waveSize = glui->add_edittext_to_panel(glui_faultPanel,"Wave Size:",
					GLUI_EDITTEXT_FLOAT,NULL,WAVESIZE_ID,glui_control);
	glui_waveSize->set_float_val(3.0);
	glui_waveSize->disable();

	glui_circleSize = glui->add_edittext_to_panel(glui_faultPanel,"Circle Size:",
					GLUI_EDITTEXT_FLOAT,NULL,CIRCLESIZE_ID,glui_control);
	glui_circleSize->set_float_val(10.0);
	glui_circleSize->disable();

	glui_particleMode = glui->add_checkbox_to_panel(glui_faultPanel,"Sticking Particles",
					NULL,PARTICLEMODE_ID,glui_control);
	glui_iterations = glui->add_spinner_to_panel(glui_faultPanel,"Add iterations:",
					GLUI_EDITTEXT_INT,NULL,ITERATIONS_ID,glui_control);
	glui_iterations->set_speed(0.000000001);
	glui_iterations->set_int_limits(0,100000,GLUI_LIMIT_CLAMP);

	glui_itDone = glui->add_edittext_to_panel(glui_faultPanel,"it. done",GLUI_EDITTEXT_INT,NULL,TOTALIT_ID,glui_control);
    glui_itDone->disable();

	glui_show = glui->add_checkbox_to_panel(glui_faultPanel,"Show",
						NULL,SHOW_ID,glui_control);
	glui_show->set_int_val(1);

	glui->add_button_to_panel(glui_faultPanel,"Stop",STOP_ID,glui_control);
	glui->add_button_to_panel(glui_faultPanel,"Start",START_ID,glui_control);
	glui_faultPanel->disable();


	glui_stepsPanel = glui->add_panel_to_panel(glui_iterate,"MidPoint Disp");
	glui_roughness = glui->add_edittext_to_panel(glui_stepsPanel,"Roughness:",
					GLUI_EDITTEXT_FLOAT,NULL,ROUGHNESS_ID,glui_control);
	glui_roughness->set_float_val(1.0);
	glui_steps = glui->add_spinner_to_panel(glui_stepsPanel,"Steps:",
					GLUI_EDITTEXT_INT,NULL,STEPS_ID,glui_control);
	glui_steps->set_speed(0.000000001);
	glui_steps->set_int_limits(1,12,GLUI_LIMIT_CLAMP);
	glui->add_button_to_panel(glui_stepsPanel,"Go!",GO_ID,glui_control);

	glui_smoothPanel = glui->add_panel("Smooth");
	glui_smooth = glui->add_spinner_to_panel(glui_smoothPanel,"k:",
					GLUI_EDITTEXT_FLOAT,NULL,-1,glui_control);
	glui_smooth->set_float_val(0.25);
	glui_smooth->set_float_limits(0.0,1.0,GLUI_LIMIT_CLAMP);
	glui->add_button_to_panel(glui_smoothPanel,"Do It!",SMOOTH_ID,glui_control);
	glui->add_separator_to_panel(glui_smoothPanel);
	glui->add_button_to_panel(glui_smoothPanel,"Show Filter Options!",OPENFILTER_ID,glui_filterControl);

	
/* Filter Options window */

	glui_filter = GLUI_Master.create_glui("Filter Options",0,0,450);

	glui_filterOptions1 = glui_filter->add_panel("Filter");

	glui_filters = glui_filter->add_listbox_to_panel(glui_filterOptions1,"Filters:",
					NULL,FILTER_ID,glui_filterControl);

	glui_filters->add_item(FilterId,"Identity");
	glui_filters->add_item(FilterAverage,"Average");
	glui_filters->add_item(FilterBlur4,"Blur (4 connected)");
	glui_filters->add_item(FilterBlur8,"Blur (8 connected)");
	glui_filters->add_item(FilterStrongBlur,"Strong Blur");

	glui_filter->add_column_to_panel(glui_filterOptions1,false);
	glui_filter->add_button_to_panel(glui_filterOptions1,"Go For It!",
					APPLYFILTER_ID,glui_filterControl);
	glui_filter->add_column_to_panel(glui_filterOptions1,false);
	glui_filter->add_button_to_panel(glui_filterOptions1,"Close Me!",CLOSEFILTER_ID,glui_filterControl);

	glui_filterOptions = glui_filter->add_panel("Matrix");

	glui_f = (GLUI_EditText **)malloc(sizeof(GLUI_EditText *) * 25);

	for(i=0;i<5;i++) {
		glui_f[i] = glui_filter->add_edittext_to_panel(glui_filterOptions,"",
					GLUI_EDITTEXT_FLOAT,NULL,F11_ID,glui_filterControl);
		glui_f[i]->set_w(10);
	}

	glui_filter->add_column_to_panel(glui_filterOptions,false);
	for(i=5;i<10;i++) {
		glui_f[i] = glui_filter->add_edittext_to_panel(glui_filterOptions,"",
					GLUI_EDITTEXT_FLOAT,NULL,F11_ID,glui_filterControl);
		glui_f[i]->set_w(10);
	}

	glui_filter->add_column_to_panel(glui_filterOptions,false);
	for(i=10;i<15;i++) {
		glui_f[i] = glui_filter->add_edittext_to_panel(glui_filterOptions,"",
					GLUI_EDITTEXT_FLOAT,NULL,F11_ID,glui_filterControl);
		glui_f[i]->set_w(10);
	}

	glui_filter->add_column_to_panel(glui_filterOptions,false);
	for(i=15;i<20;i++) {
		glui_f[i] = glui_filter->add_edittext_to_panel(glui_filterOptions,"",
					GLUI_EDITTEXT_FLOAT,NULL,F11_ID,glui_filterControl);
		glui_f[i]->set_w(10);
	}

	glui_filter->add_column_to_panel(glui_filterOptions,false);
	for(i=20;i<25;i++) {
		glui_f[i] = glui_filter->add_edittext_to_panel(glui_filterOptions,"",
					GLUI_EDITTEXT_FLOAT,NULL,F11_ID,glui_filterControl);
		glui_f[i]->set_w(10);
	}
	glui_f[12]->set_float_val(1.0);


/* Navigation Window */
	glui_bottom = GLUI_Master.create_glui_subwindow(mainWindow,GLUI_SUBWINDOW_BOTTOM);

	glui_rotate = glui_bottom->add_rotation("Rotation",m);
	glui_rotate->set_spin(0.95);
	glui_rotate->reset();

	glui_bottom->add_column(false);

    glui_transXY = glui_bottom->add_translation("XY", GLUI_TRANSLATION_XY, trans);
	glui_bottom->add_column(false);

	glui_transX = glui_bottom->add_translation("X",GLUI_TRANSLATION_X,trans);
	glui_bottom->add_column(false);

	glui_transY = glui_bottom->add_translation("Y",GLUI_TRANSLATION_Y,&trans[1]);
	glui_bottom->add_column(false);

	glui_transZ = glui_bottom->add_translation("Z",GLUI_TRANSLATION_Z,&trans[2]);
	glui_bottom->add_column(true);

	glui_navModeLB = glui_bottom->add_listbox("Navigation",NULL,NAVIGATION_ID,glui_control);
	glui_navModeLB->add_item(EXAMINE,"Examine");
	glui_navModeLB->add_item(WALKFLY,"Fly");

	glui_bottom->add_statictext("");

	glui_bottom->add_button( "Quit", 0,quit/*(GLUI_Update_CB)exit*/ );

	glui_bottom->set_main_gfx_window( mainWindow );
	glui->set_main_gfx_window( mainWindow );
	glui_filter->set_main_gfx_window( mainWindow );



	// init terrain structures
	terrainInit(128,128);
	initScene();


	glutMainLoop();

	return(0);
}
