/*
*Se necesita instalar FreeImage
*sudo apt-get install libfreeimage3 libfreeimage-dev 
* compilar ej:  g++ -Wall -o test main00.cpp -lglut -lGL -lGLU -lfreeimage
*/
/*
CC322 computacion grafica 2018-2, 5/Oct/2018, Carlos Espinoza Mansilla
*/

#include <iostream>
#include <stdlib.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <FreeImage.h>
#include <assert.h>
#include <fstream>


#define numTEXT 0
#define numTEXT1 0

GLuint texID[numTEXT];
GLuint texID1[numTEXT1];
GLuint texID2[numTEXT1];

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
    FREE_IMAGE_FORMAT format = FreeImage_GetFIFFromFilename("pasto.jpg");
    if (format == FIF_UNKNOWN) {
       printf("Archivo de Imagen desconocido \n");
       }
    FIBITMAP* bitmap = FreeImage_Load(format, "pasto.jpg", 0);  //Leer Imagen.
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

void loadTextures1() {
 	glGenTextures(numTEXT1,texID1);  // Obtener el Id textura .
    void* imgData1;      // Puntero a data del Archivo.
    int imgWidth;   // Ancho de Imagen
    int imgHeight;  // Alto.
    FREE_IMAGE_FORMAT format1 = FreeImage_GetFIFFromFilename("montania.jpg");
    if (format1 == FIF_UNKNOWN) {
       printf("Archivo de Imagen desconocido \n");
       }
    FIBITMAP* bitmap = FreeImage_Load(format1, "montania.jpg", 0);  //Leer Imagen.
    if (!bitmap) {
        printf("Fallo la carga de imagen \n");
    }
    FIBITMAP* bitmap2 = FreeImage_ConvertTo24Bits(bitmap);  // Convierte a RGB
    FreeImage_Unload(bitmap);
    imgData1 = FreeImage_GetBits(bitmap2);
    imgWidth = FreeImage_GetWidth(bitmap2);
    imgHeight = FreeImage_GetHeight(bitmap2);
    if (imgData1) {
         printf("Textura cargada, tamanio %dx%d\n", imgWidth, imgHeight);
         int format1; // Formato del color.
         if ( FI_RGBA_RED == 0 ){
            format1 = GL_RGB;
		}
         else{
            format1 = GL_BGR;
            }
		glBindTexture( GL_TEXTURE_2D, texID2[0] );  // Cargando textura
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgWidth, imgHeight, 0, format1,GL_UNSIGNED_BYTE, imgData1);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        }
        else {
            printf("Fallo la carga de textura \n");
        }
}


void loadTextures2() {
 	glGenTextures(numTEXT1,texID2);  // Obtener el Id textura .
    void* imgData1;      // Puntero a data del Archivo.
    int imgWidth;   // Ancho de Imagen
    int imgHeight;  // Alto.
    FREE_IMAGE_FORMAT format1 = FreeImage_GetFIFFromFilename("cielo.jpg");
    if (format1 == FIF_UNKNOWN) {
       printf("Archivo de Imagen desconocido \n");
       }
    FIBITMAP* bitmap = FreeImage_Load(format1, "cielo.jpg", 0);  //Leer Imagen.
    if (!bitmap) {
        printf("Fallo la carga de imagen \n");
    }
    FIBITMAP* bitmap2 = FreeImage_ConvertTo24Bits(bitmap);  // Convierte a RGB
    FreeImage_Unload(bitmap);
    imgData1 = FreeImage_GetBits(bitmap2);
    imgWidth = FreeImage_GetWidth(bitmap2);
    imgHeight = FreeImage_GetHeight(bitmap2);
    if (imgData1) {
         printf("Textura cargada, tamanio %dx%d\n", imgWidth, imgHeight);
         int format1; // Formato del color.
         if ( FI_RGBA_RED == 0 ){
            format1 = GL_RGB;
		}
         else{
            format1 = GL_BGR;
            }
		glBindTexture( GL_TEXTURE_2D, texID1[0] );  // Cargando textura
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgWidth, imgHeight, 0, format1,GL_UNSIGNED_BYTE, imgData1);
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
	
	loadTextures();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texID[0]);
	
	//Bottom
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glColor3f(0.2f, 1.0f, 0.2f);  //CAMBIAR COLOR
	glBegin(GL_QUADS);
	
	glNormal3f(0.0, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-2.5f, -2.5f, 2.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(2.5f, -2.5f, 2.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(2.5f, -2.5f, -2.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-2.5f, -2.5f, -2.5f);
	
	glEnd();
	
	glDisable(GL_TEXTURE_2D);

	loadTextures1();
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texID1[0]);
	
	
	//Back
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glColor3f(0.9f, 0.9f, 1.0f);
	glBegin(GL_TRIANGLES);
		
	//modificando forma en que se muestra imagen
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.1f, 0.1f);
	glVertex3f(-2.5f, -2.5f, -2.5f);
	glTexCoord2f(0.7f, 0.7f);
	glVertex3f(0.0f, 2.5f, -2.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(2.5f, -2.5f, -2.5f);
	
	glEnd();
	
	//Left   AGREGANDO TEXTURA AL COSTADO
	glDisable(GL_TEXTURE_2D);	

	loadTextures1();
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texID1[0]);
	
	
	
	glColor3f(0.9f, 0.9f, 1.0f);
	glBegin(GL_QUADS);
	
	glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-2.5f, -2.5f, 2.5f);
		glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-2.5f, -2.5f, -2.5f);
		glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-2.5f, 2.5f, -2.5f);
		glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-2.5f, 2.5f, 2.5f);
	
	glEnd();
	
	
	/** AGREGANDO CIELO **/
	
	glDisable(GL_TEXTURE_2D);

	loadTextures2();
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texID2[0]);
	
		
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glColor3f(0.9f, 0.9f, 1.0f);
	glBegin(GL_QUADS);
		
	
	glNormal3f(0.0, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-5.5f, -4.0f, -6.5f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(5.5f, -4.0f, -6.5f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(5.5f, 5.5f, -6.5f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-5.5f, 5.5f, -6.5f);
	
	
	glEnd();
	
	/*Crear cubo*/
	
	
	glutSwapBuffers();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	
	glutCreateWindow("CC322-PCL3");
	initRendering();
	
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);
	
	glutMainLoop();
	return 0;
}









