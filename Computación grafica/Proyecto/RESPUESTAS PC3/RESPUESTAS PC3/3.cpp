// CC322 PRACTICA CALIFICADA 3 VICTOR PONCE PINEDO 20160431D

/*
*Se necesita instalar FreeImage
*sudo apt-get install libfreeimage3 libfreeimage-dev 
* compilar ej:  g++ -Wall -o test main00.cpp -lglut -lGL -lGLU -lfreeimage
*/

#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include <FreeImage.h>
#include <assert.h>
#include <fstream>

#include<math.h>
#include <vector>
#include <stdio.h>
#include <string>
#include <cstring>
#include <glm/glm.hpp>
#include<GLFW/glfw3.h>
#include<GL/glu.h>


#define numTEXT 1
#define numTEXT_2 1

GLuint texID[numTEXT];
GLuint texID_2[numTEXT_2];
float  fx=0;

using namespace std;
std::vector< glm::vec3 > vertices_gl;
	std::vector< glm::vec2 > uvs_gl;
	std::vector< glm::vec3 > normals_gl;



bool loadOBJ(
	const char * path, 
	std::vector<glm::vec3> & out_vertices, 
	std::vector<glm::vec2> & out_uvs,
	std::vector<glm::vec3> & out_normals
){
	printf("Loading OBJ file %s...\n", path);

	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3> temp_vertices; 
	std::vector<glm::vec2> temp_uvs;
	std::vector<glm::vec3> temp_normals;


	FILE * file = fopen(path, "r");
	if( file == NULL ){
		printf("Impossible to open the file ! Are you in the right path ? See Tutorial 1 for details\n");
		getchar();
		return false;
	}

	while( 1 ){

		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

		// else : parse lineHeader
		
		if ( strcmp( lineHeader, "v" ) == 0 ){
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
			temp_vertices.push_back(vertex);
		}else if ( strcmp( lineHeader, "vt" ) == 0 ){
			glm::vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y );
			// uv.y = -uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
			temp_uvs.push_back(uv);
		}else if ( strcmp( lineHeader, "vn" ) == 0 ){
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
			temp_normals.push_back(normal);
		}else if ( strcmp( lineHeader, "f" ) == 0 ){
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );

			if (matches != 9){
				printf("MATCHES=%d   File can't be read by our simple parser :-( Try exporting with other options\n",matches);
				fclose(file);
				return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices    .push_back(uvIndex[0]);
			uvIndices    .push_back(uvIndex[1]);
			uvIndices    .push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}else{
			// Probably a comment, eat up the rest of the line
			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
		}

	}

	// For each vertex of each triangle
	for( unsigned int i=0; i<vertexIndices.size(); i++ ){

		// Get the indices of its attributes
		unsigned int vertexIndex = vertexIndices[i];
		unsigned int uvIndex = uvIndices[i];
		unsigned int normalIndex = normalIndices[i];
		
		// Get the attributes thanks to the index
		glm::vec3 vertex = temp_vertices[ vertexIndex-1 ];
		glm::vec2 uv = temp_uvs[ uvIndex-1 ];
		glm::vec3 normal = temp_normals[ normalIndex-1 ];
		
		// Put the attributes in buffers
		out_vertices.push_back(vertex);
		out_uvs     .push_back(uv);
		out_normals .push_back(normal);
	
	}
	fclose(file);
	return true;
}




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



void initRendering() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	loadTextures_2();
	loadTextures();
}

void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (float)w / (float)h, 1.0, 200.0);
	gluLookAt(2.0, 0.0, 2.0, 0.0, 0.0, 0, 0.0, 1.0, 1.0);
}

void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
    	glLoadIdentity();
	
	glTranslatef(0.0f, 0.0f, -5.0f);
	
	GLfloat ambientLight[] = {0.2f, 0.2f, 0.2f, 1.0f};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
	
	GLfloat directedLight[] = {0.7f, 0.7f, 0.7f, 1.0f};
	GLfloat directedLightPos[] = {-10.0f, 15.0f, 20.0f, 0.0f};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, directedLight);
	glLightfv(GL_LIGHT0, GL_POSITION, directedLightPos);
	
	//glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texID[0]);
	
	//Bottom
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glColor3f(0.5f, 1.0f, 0.5f);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texID_2[0]);
	
	//Back
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glColor3f(0.5f, 1.0f, 0.5f);

	


	for(int i=0 ; i<36 ; i=i+3){
		printf("*** TRIANGULO DE VERTICES  (%f  %f  %f)  (%f  %f  %f)   (%f  %f  %f)    \n",(&vertices_gl[i])->x,(&vertices_gl[i])->y,(&vertices_gl[i])->z,(&vertices_gl[i+1])->x,(&vertices_gl[i+1])->y,(&vertices_gl[i+1])->z,(&vertices_gl[i+2])->x,(&vertices_gl[i+2])->y,(&vertices_gl[i+2])->z );
		if(i%3==0)
			glColor3f(0.0f, 1.0f, 0.0f);
		else if(i%3==1)
			glColor3f(0.0f, 0.0f, 1.0f);
		else if(i%3==2)
			glColor3f(1.0f, 0.0f, 0.0f);
		glPushMatrix();
		//glRotatef(fx,0,1,0);
		glBegin(GL_TRIANGLE_STRIP);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f((&vertices_gl[i])->x,(&vertices_gl[i])->y,(&vertices_gl[i])->z);
		//std::cout << "nums contains " << vertices_gl.size() << " elements.\n";
		//glColor3f(1.0f, 0.0f, 0.0f);	
		glVertex3f((&vertices_gl[i+1])->x,(&vertices_gl[i+1])->y,(&vertices_gl[i+1])->z);
		//std::cout << "nums contains " << vertices_gl.size() << " elements.\n";
		//glColor3f(0.0f, 1.0f, 1.0f);		
		glVertex3f((&vertices_gl[i+2])->x,(&vertices_gl[i+2])->y,(&vertices_gl[i+2])->z);
		//std::cout << "nums contains " << vertices_gl.size() << " elements.\n";
		glEnd();

	}

	//glDisable(GL_TEXTURE_2D);
	//fx=fx+0.2;
	glPopMatrix();
	//printf("/*/*/* %f /*/*/*\n",fx);
	glutSwapBuffers();
}

int main(int argc, char** argv) {
	

	bool res = loadOBJ("cubo.obj", vertices_gl, uvs_gl, normals_gl);

	std::cout << "nums contains " << vertices_gl.size() << " elements.\n";
	std::cout << "nums contains " << uvs_gl.size() << " elements.\n";
	std::cout << "nums contains " << normals_gl.size() << " elements.\n";
	for(int i{0}; i<36; i++){
	    std::cout<<"\n";
	    for(int j{0}; j<3; j++){
	    std::cout<<vertices_gl[i][j]<<" ";
	    }
	}


	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1500, 1500);
	
	glutCreateWindow("CC322-PCL3");
	initRendering();
	//glutIdleFunc(drawScene);
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);
	
	glutMainLoop();
	return 0;
}









