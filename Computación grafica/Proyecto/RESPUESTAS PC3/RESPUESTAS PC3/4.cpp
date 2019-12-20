// CC322 PRACTICA CALIFICADA 3 VICTOR PONCE PINEDO 20160431D


/*
*Se necesita instalar FreeImage
*sudo apt-get install libfreeimage3 libfreeimage-dev 
* compilar ej:  g++ -Wall -o test main00.cpp -lglut -lGL -lGLU -lfreeimage
*/

#include <iostream>
#include <stdlib.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <FreeImage.h>
#include <assert.h>
#include <fstream>


#define numTEXT 1
#define numTEXT_2 1
#define numTEXT_3 1

GLuint texID[numTEXT];
GLuint texID_2[numTEXT_2];
GLuint texID_3[numTEXT_3];


using namespace std;

void handleKeypress(unsigned char key, int x, int y) {
	switch (key) {
		case 27: //Escape key
			exit(0);
	}
}

 //Cargando Texturas
void loadTextures() {
 	glGenTextures(numTEXT,texID);  // Obtener el Id textura .
    void* imgData;      // Puntero a data del Archivo.
    int imgWidth;   // Ancho de Imagen
    int imgHeight;  // Alto.
    FREE_IMAGE_FORMAT format = FreeImage_GetFIFFromFilename("pastito.jpg");
    if (format == FIF_UNKNOWN) {
       printf("Archivo de Imagen desconocido \n");
       }
    FIBITMAP* bitmap = FreeImage_Load(format, "pastito.jpg", 0);  //Leer Imagen.
    if (!bitmap) {
        printf("Fallo la carga de imagen \n");
    }
    FIBITMAP* bitmap2 = FreeImage_ConvertTo24Bits(bitmap);  // Convierte a RGB
    FreeImage_Unload(bitmap);
    imgData = FreeImage_GetBits(bitmap2);
    imgWidth = FreeImage_GetWidth(bitmap2);
    imgHeight = FreeImage_GetHeight(bitmap2);
    if (imgData) {
         printf("Textura cargada, tamanio %dx%d\n", imgWidth, imgHeight);
         int format; // Formato del color.
         if ( FI_RGBA_RED == 0 ){
            format = GL_RGB;
		}
         else{
            format = GL_BGR;
            }
		glBindTexture( GL_TEXTURE_2D, texID[0] );  // Cargando textura
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgWidth, imgHeight, 0, format,GL_UNSIGNED_BYTE, imgData);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        }
        else {
            printf("Fallo la carga de textura \n");
        }
}


void loadTextures_2() {
 	glGenTextures(numTEXT_2,texID_2);  // Obtener el Id textura .
    void* imgData2;      // Puntero a data del Archivo.
    int imgWidth2;   // Ancho de Imagen
    int imgHeight2;  // Alto.
    FREE_IMAGE_FORMAT format = FreeImage_GetFIFFromFilename("cerritos.jpg");
    if (format == FIF_UNKNOWN) {
       printf("Archivo de Imagen desconocido \n");
       }
    FIBITMAP* bitmap = FreeImage_Load(format, "cerritos.jpg", 1);  //Leer Imagen.
    if (!bitmap) {
        printf("Fallo la carga de imagen \n");
    }
    FIBITMAP* bitmap2 = FreeImage_ConvertTo24Bits(bitmap);  // Convierte a RGB
    FreeImage_Unload(bitmap);
    imgData2 = FreeImage_GetBits(bitmap2);
    imgWidth2 = FreeImage_GetWidth(bitmap2);
    imgHeight2 = FreeImage_GetHeight(bitmap2);
    if (imgData2) {
         printf("Textura cargada, tamanio %dx%d\n", imgWidth2, imgHeight2);
         int format; // Formato del color.
         if ( FI_RGBA_RED == 0 ){
            format = GL_RGB;
		}
         else{
            format = GL_BGR;
            }
		glBindTexture( GL_TEXTURE_2D, texID_2[0] );  // Cargando textura
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgWidth2, imgHeight2, 0, format,GL_UNSIGNED_BYTE, imgData2);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        }
        else {
            printf("Fallo la carga de textura \n");
        }
}

void loadTextures_3() {
 	glGenTextures(numTEXT_3,texID_3);  // Obtener el Id textura .
    void* imgData2;      // Puntero a data del Archivo.
    int imgWidth2;   // Ancho de Imagen
    int imgHeight2;  // Alto.
    FREE_IMAGE_FORMAT format = FreeImage_GetFIFFromFilename("nubes.jpg");
    if (format == FIF_UNKNOWN) {
       printf("Archivo de Imagen desconocido \n");
       }
    FIBITMAP* bitmap = FreeImage_Load(format, "nubes.jpg", 2);  //Leer Imagen.
    if (!bitmap) {
        printf("Fallo la carga de imagen \n");
    }
    FIBITMAP* bitmap2 = FreeImage_ConvertTo24Bits(bitmap);  // Convierte a RGB
    FreeImage_Unload(bitmap);
    imgData2 = FreeImage_GetBits(bitmap2);
    imgWidth2 = FreeImage_GetWidth(bitmap2);
    imgHeight2 = FreeImage_GetHeight(bitmap2);
    if (imgData2) {
         printf("Textura cargada, tamanio %dx%d\n", imgWidth2, imgHeight2);
         int format; // Formato del color.
         if ( FI_RGBA_RED == 0 ){
            format = GL_RGB;
		}
         else{
            format = GL_BGR;
            }
		glBindTexture( GL_TEXTURE_2D, texID_3[0] );  // Cargando textura
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgWidth2, imgHeight2, 0, format,GL_UNSIGNED_BYTE, imgData2);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        }
        else {
            printf("Fallo la carga de textura \n");
        }
}




void initRendering() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	loadTextures_3();	
	loadTextures_2();
	loadTextures();
}

void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (float)w / (float)h, 1.0, 200.0);
}

void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	
	glTranslatef(0.0f, 1.0f, -6.0f);
	
	GLfloat ambientLight[] = {0.2f, 0.2f, 0.2f, 1.0f};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
	
	GLfloat directedLight[] = {0.7f, 0.7f, 0.7f, 1.0f};
	GLfloat directedLightPos[] = {-10.0f, 15.0f, 20.0f, 0.0f};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, directedLight);
	glLightfv(GL_LIGHT0, GL_POSITION, directedLightPos);
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texID[0]);
	
	//Bottom
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glColor3f(0.5f, 1.0f, 0.5f);
	glBegin(GL_QUADS);
	
	glNormal3f(0.0, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-2.5f, -2.5f, 2.5f);
	glTexCoord2f(-1.0f, 0.0f);
	glVertex3f(2.5f, -2.5f, 2.5f);
	glTexCoord2f(-1.0f, -1.0f);
	glVertex3f(2.5f, -2.5f, -2.5f);
	glTexCoord2f(0.0f,-1.0f);
	glVertex3f(-2.5f, -2.5f, -2.5f);
	
	glEnd();
	
	glDisable(GL_TEXTURE_2D);
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texID_2[0]);
	
	//Back
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glColor3f(0.5f, 1.0f, 0.5f);
	glBegin(GL_QUADS);
	glNormal3f(0.0, 1.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-2.5f, 0.5f, -2.5f);   // vertice inferior izquierdo
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-2.5f, -2.5f, -2.5f);     // vertice superior del medio
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(2.5f, -2.5f, -2.5f);     // vertice superior del medio
	glTexCoord2f(0.0f,1.0f);
	glVertex3f(2.5f, 0.5f, -2.5f);     // vertice superior del medio


	glEnd();
	
	//Left
	glDisable(GL_TEXTURE_2D);
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texID_2[0]);
	
	//Back
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glColor3f(0.5f, 1.0f, 0.5f);
	glBegin(GL_QUADS);
	
	glNormal3f(0.0f, 1.0f, 0.0f);
        glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-2.5f, -2.5f, 2.5f);    
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-2.5f, -2.5f, -2.5f);
	glTexCoord2f(0.0f, 1.0f);	
	glVertex3f(-2.5f, 0.5f, -2.5f);
        glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-2.5f, -0.5f, 2.5f);
	
	glEnd();
	glDisable(GL_TEXTURE_2D);


glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texID_2[0]);
	
	//Back
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glColor3f(0.5f, 1.0f, 0.5f);
	glBegin(GL_QUADS);
	
	glNormal3f(0.0f, 1.0f, 0.0f);
        glTexCoord2f(1.0f, 0.0f);
	glVertex3f(+2.5f, -2.5f, 2.5f);    
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(+2.5f, -2.5f, -2.5f);
	glTexCoord2f(0.0f, 1.0f);	
	glVertex3f(+2.5f, 0.5f, -2.5f);
        glTexCoord2f(1.0f, 1.0f);
	glVertex3f(+2.5f, -0.5f, 2.5f);
	
	glEnd();
	glDisable(GL_TEXTURE_2D);


        glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texID_3[0]);
	
	//Back
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glColor3f(0.5f, 1.0f, 0.5f);
	glBegin(GL_QUADS);
	
	glNormal3f(0.0f, 1.0f, 0.0f);
        glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-2.5f, 1.5+(-2.5f), 2.5f);    
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-2.5f, 1.5+(-2.5f), -2.5f);
	glTexCoord2f(0.0f, 1.0f);	
	glVertex3f(-2.5f, 1.5+(0.5f), -2.5f);
        glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-2.5f, 1.5+-(0.5f), 2.5f);
	
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texID_3[0]);
	
	//Back
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glColor3f(0.5f, 1.0f, 0.5f);
	glBegin(GL_QUADS);
	
	glNormal3f(0.0, 1.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-2.5f, 1.5+0.5f, -2.5f);   // vertice inferior izquierdo
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-2.5f, 1.5+1-2.5f, -2.5f);     // vertice superior del medio
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(2.5f, 1.5+-2.5f, -2.5f);     // vertice superior del medio
	glTexCoord2f(0.0f,1.0f);
	glVertex3f(2.5f, 1.5+0.5f, -2.5f);     // vertice superior del medio
	glEnd();
	glDisable(GL_TEXTURE_2D);

  glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texID_3[0]);
	
	//Back
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glColor3f(0.5f, 1.0f, 0.5f);
	glBegin(GL_QUADS);
	
	glNormal3f(0.0f, 1.0f, 0.0f);
        glTexCoord2f(1.0f, 0.0f);
	glVertex3f(+2.5f, 1.5+(-2.5f), 2.5f);    
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(+2.5f, 1.5+(-2.5f), -2.5f);
	glTexCoord2f(0.0f, 1.0f);	
	glVertex3f(+2.5f, 1.5+(0.5f), -2.5f);
        glTexCoord2f(1.0f, 1.0f);
	glVertex3f(+2.5f, 1.5+-(0.5f), 2.5f);
	
	glEnd();
	glDisable(GL_TEXTURE_2D);



	glutSwapBuffers();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1500, 1500);
	
	glutCreateWindow("CC322-PCL3");
	initRendering();
	
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);
	
	glutMainLoop();
	return 0;
}









