#include <math.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include "tga.h"
#include "terrain.h"
#include <FreeImage.h>

// VARIABLES Y FUNCIONES PARA EL TEXTURIZADO //
#define numTEXT 0

GLuint texID[numTEXT];

 //Cargando Texturas
void loadTextures(const char* NOMTEXT) {
 	glGenTextures(numTEXT,texID);  // Obtener el Id textura .
    void* imgData;      // Puntero a data del Archivo.
    int imgWidth;   // Ancho de Imagen
    int imgHeight;  // Alto.
    FREE_IMAGE_FORMAT format = FreeImage_GetFIFFromFilename(NOMTEXT);
    if (format == FIF_UNKNOWN) {
       printf("Archivo de Imagen desconocido \n");
       }
    FIBITMAP* bitmap = FreeImage_Load(format, NOMTEXT, 0);  //Leer Imagen.
    if (!bitmap) {
        printf("Fallo la carga de imagen \n");
    }
    FIBITMAP* bitmap2 = FreeImage_ConvertTo24Bits(bitmap);  // Convierte a RGB
    FreeImage_Unload(bitmap);
    imgData = FreeImage_GetBits(bitmap2);
    imgWidth = FreeImage_GetWidth(bitmap2);
    imgHeight = FreeImage_GetHeight(bitmap2);
    if (imgData) {
         //printf("Textura cargada, tamanio %dx%d\n", imgWidth, imgHeight);
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

///////////////////////////

static int terrainGridWidth ,terrainGridLength;
static float *terrainHeights = NULL;
static float *terrainColors = NULL;
static float *terrainNormals = NULL;


float *terrainCrossProduct(int x1,int z1,int x2,int z2,int x3,int z3) {

	float *auxNormal,v1[3],v2[3];
		
	v1[0] = x2-x1; 
	v1[1] = -terrainHeights[z1 * terrainGridWidth + x1] 
			+ terrainHeights[z2 * terrainGridWidth + x2];
	v1[2] = z2-z1; 


	v2[0] = x3-x1; 
	v2[1] = -terrainHeights[z1 * terrainGridWidth + x1] 
			+ terrainHeights[z3 * terrainGridWidth + x3];
	v2[2] = z3-z1; 

	auxNormal = (float *)malloc(sizeof(float)*3);

	auxNormal[2] = v1[0] * v2[1] - v1[1] * v2[0];
	auxNormal[0] = v1[1] * v2[2] - v1[2] * v2[1];
	auxNormal[1] = v1[2] * v2[0] - v1[0] * v2[2];

	return(auxNormal);
}

void terrainNormalize(float *v) {

	double d,x,y,z;

	x = v[0];
	y = v[1];
	z = v[2];
	
	d = sqrt((x*x) + (y*y) + (z*z));

	v[0] = x / d;
	v[1] = y / d;
	v[2] = z / d;
}

void terrainAddVector(float *a, float *b) {

	a[0] += b[0];
	a[1] += b[1];
	a[2] += b[2];
}

void terrainComputeNormals() {

	float *norm1,*norm2,*norm3,*norm4; 
	int i,j,k;
	
	if (terrainNormals == NULL)
		return;

	for(i = 0; i < terrainGridLength; i++)
		for(j = 0; j < terrainGridWidth; j++) {
			norm1 = NULL;
			norm2 = NULL;
			norm3 = NULL;
			norm4 = NULL;

			// NORMALES PARA LAS ESQUINAS
			if (i == 0 && j == 0) {
				norm1 = terrainCrossProduct(0,0, 0,1, 1,0);	
				terrainNormalize(norm1);				
			}
			else if (j == terrainGridWidth-1 && i == terrainGridLength-1) {
				norm1 = terrainCrossProduct(i,j, j,i-1, j-1,i);	
				terrainNormalize(norm1);				
			}
			else if (j == 0 && i == terrainGridLength-1) {
				norm1 = terrainCrossProduct(i,j, j,i-1, j+1,i);	
				terrainNormalize(norm1);				
			}
			else if (j == terrainGridWidth-1 && i == 0) {
				norm1 = terrainCrossProduct(i,j, j,i+1, j-1,i);	
				terrainNormalize(norm1);				
			}

			// NORMALES PARA LOS BORDES
			else if (i == 0) {
				norm1 = terrainCrossProduct(j,0, j-1,0, j,1);
				terrainNormalize(norm1);
				norm2 = terrainCrossProduct(j,0,j,1,j+1,0);
				terrainNormalize(norm2);
			}
			else if (j == 0) {
				norm1 = terrainCrossProduct(0,i, 1,i, 0,i-1);
				terrainNormalize(norm1);
				norm2 = terrainCrossProduct(0,i, 0,i+1, 1,i);
				terrainNormalize(norm2);
			}
			else if (i == terrainGridLength) {
				norm1 = terrainCrossProduct(j,i, j,i-1, j+1,i);
				terrainNormalize(norm1);
				norm2 = terrainCrossProduct(j,i, j+1,i, j,i-1);
				terrainNormalize(norm2);
			}
			else if (j == terrainGridWidth) {
				norm1 = terrainCrossProduct(j,i, j,i-1, j-1,i);
				terrainNormalize(norm1);
				norm2 = terrainCrossProduct(j,i, j-1,i, j,i+1);
				terrainNormalize(norm2);
			}

			// NORMALES PARA EL INTERIOR
			else {
				norm1 = terrainCrossProduct(j,i, j-1,i, j,i+1);
				terrainNormalize(norm1);
				norm2 = terrainCrossProduct(j,i, j,i+1, j+1,i);
				terrainNormalize(norm2);
				norm3 = terrainCrossProduct(j,i, j+1,i, j,i-1);
				terrainNormalize(norm3);
				norm4 = terrainCrossProduct(j,i, j,i-1, j-1,i);
				terrainNormalize(norm4);
			}
			if (norm2 != NULL) {
				terrainAddVector(norm1,norm2);
				free(norm2);
			}
			if (norm3 != NULL) {
				terrainAddVector(norm1,norm3);
				free(norm3);
			}
			if (norm4 != NULL) {
				terrainAddVector(norm1,norm4);
				free(norm4);
			}
			terrainNormalize(norm1);
			norm1[2] = - norm1[2];
			for (k = 0; k< 3; k++) 
				terrainNormals[3*(i*terrainGridWidth + j) + k] = norm1[k];
			free(norm1);
		}

}


int terrainLoadFromImage(char *filename, int normals) {

	tgaInfo *info;
	int mode;
	float pointHeight;

// SI YA EXISTE EL TERRENO, DESTRUYE EL ANTERIOR
	if (terrainHeights != NULL)
		terrainDestroy();
		
// CARGAR LA IMAGEN USANDO EL LECTOR DE TGA
	info = tgaLoad(filename);
// REVISAR SI LA IMAGEN FUE CORRECTAMENTE CARGADA
	if (info->status != TGA_OK)
		return(TERRAIN_ERROR_LOADING_IMAGE);
// SI SE CARGA UNA IMAGEN QUE NO ES BLANCO Y NEGRO, TRANSFORMARLA A BLANCO Y NEGRO
	mode = info->pixelDepth / 8;
	if (mode == 3) {
		tgaRGBtoGreyscale(info);
		mode = 1;
	}
	
// ESTABLECER ANCHO Y ALTURA DEL TERRENO
	terrainGridWidth = info->width;
	terrainGridLength = info->height;

// ASIGNAR
	terrainHeights = (float *)malloc(terrainGridWidth * terrainGridLength * sizeof(float));
	if (terrainHeights == NULL)
		return(TERRAIN_ERROR_MEMORY_PROBLEM);

// ASIGNAR MEMORIA PARA LAS NORMALES, Y REVISAR SI HAY ERRORES
	if (normals) {
		terrainNormals = (float *)malloc(terrainGridWidth * terrainGridLength * sizeof(float) * 3);
		if (terrainNormals == NULL)
			return(TERRAIN_ERROR_MEMORY_PROBLEM);
	}
	else
			terrainNormals = NULL;
	if (mode == 4) {
		terrainColors = (float *)malloc(terrainGridWidth * terrainGridLength * sizeof(float)*3);
		if (terrainColors == NULL)
			return(TERRAIN_ERROR_MEMORY_PROBLEM);
	}
	else
		terrainColors = NULL;

// LLENADO DE ARRAYS
	for (int i = 0 ; i < terrainGridLength; i++)
		for (int j = 0;j < terrainGridWidth; j++) {
// CALCULAR LAS ALTURAS CON VALORES DE 0 A 1
			pointHeight = info->imageData[mode*(i*terrainGridWidth + j)+(mode-1)] / 256.0;
			terrainHeights[i*terrainGridWidth + j] = pointHeight;

			if (mode==4) {
				terrainColors[3*(i*terrainGridWidth + j)]   = info->imageData[mode*(i*terrainGridWidth + j)] / 256.0;
				terrainColors[3*(i*terrainGridWidth + j)+1] = info->imageData[mode*(i*terrainGridWidth + j)+1]/256.0;
				terrainColors[3*(i*terrainGridWidth + j)+2] = info->imageData[mode*(i*terrainGridWidth + j)+2]/256.0;
			}
		}
// CALCULAR NORMALES	
	if (normals)
		terrainComputeNormals();
// LIBERAR MEMORIA
	tgaDestroy(info);
	
	return(TERRAIN_OK); 
}

int terrainScale(float min,float max) {

	float amp,aux,min1,max1,height;
	int total,i;

	if (terrainHeights == NULL)
		return(TERRAIN_ERROR_NOT_INITIALISED);

	if (min > max) {
		aux = min;
		min = max;
		max = aux;
	}

	amp = max - min;
	total = terrainGridWidth * terrainGridLength;

	min1 = terrainHeights[0];
	max1 = terrainHeights[0];
	for(i=1;i < total ; i++) {
		if (terrainHeights[i] > max1)
			max1 = terrainHeights[i];
		if (terrainHeights[i] < min1)
			min1 = terrainHeights[i];
	}
	for(i=0;i < total; i++) {
		height = (terrainHeights[i] - min1) / (max1-min1);
		terrainHeights[i] = height * amp - min;
	}

	if (terrainNormals != NULL)
		terrainComputeNormals();
	return(TERRAIN_OK);
}
	
int terrainCreateDL(float xOffset, float yOffset, float zOffset) {

	GLuint terrainDL;
	float startW,startL;
	int i,j;

	startW = terrainGridWidth / 2.0 - terrainGridWidth;
	startL = - terrainGridLength / 2.0 + terrainGridLength;

	terrainDL = glGenLists(1);

	glNewList(terrainDL,GL_COMPILE);
	if (terrainNormals != NULL && terrainColors != NULL) {
		glColorMaterial(GL_FRONT, GL_DIFFUSE);
		glEnable(GL_COLOR_MATERIAL);
	}
	
	
	//TEXTURIZADO//
        
        glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);	
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        //////////////////////

		
	//AQUI SE ESTABLECE LA MATRIZ DE PUNTOS QUE CREARAN EL TERRENO
	
	for (i = 0 ; i < terrainGridLength-1; i++) {
		glBegin(GL_TRIANGLE_STRIP);
		for (j = 0;j < terrainGridWidth; j=j+2) {
		    if(terrainHeights[(i)*terrainGridWidth + (j)] < 0.5){ 
		        loadTextures("roca.jpg");
	                glEnable(GL_TEXTURE_2D);
	                glBindTexture(GL_TEXTURE_2D, texID[0]);	
			if (terrainColors != NULL) 
				glColor3f(terrainColors[3*((i+1)*terrainGridWidth + j)],
					  terrainColors[3*((i+1)*terrainGridWidth + j)+1],
					  terrainColors[3*((i+1)*terrainGridWidth + j)+2]);
			if (terrainNormals != NULL)
				glNormal3f(terrainNormals[3*((i+1)*terrainGridWidth + j)],
					   terrainNormals[3*((i+1)*terrainGridWidth + j)+1],
					   terrainNormals[3*((i+1)*terrainGridWidth + j)+2]);
			glTexCoord2f(0.0f, 0.0f);			  
			glVertex3f(
				startW + j + xOffset,
				terrainHeights[(i+1)*terrainGridWidth + (j)] + yOffset,
				startL - (i+1) + zOffset);

			if (terrainColors != NULL) 
				glColor3f(terrainColors[3*(i*terrainGridWidth + j)],
					  terrainColors[3*(i*terrainGridWidth + j)+1],
					  terrainColors[3*(i*terrainGridWidth + j)+2]);
			if (terrainNormals != NULL)
				glNormal3f(terrainNormals[3*(i*terrainGridWidth + j)],
					   terrainNormals[3*(i*terrainGridWidth + j)+1],
					   terrainNormals[3*(i*terrainGridWidth + j)+2]);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(
				startW + j + xOffset, 
				terrainHeights[(i)*terrainGridWidth + j] + yOffset,
				startL - i + zOffset);		



			if (terrainColors != NULL) 
				glColor3f(terrainColors[3*((i+1)*terrainGridWidth + (j+1))],
					  terrainColors[3*((i+1)*terrainGridWidth + (j+1))+1],
					  terrainColors[3*((i+1)*terrainGridWidth + (j+1))+2]);
			if (terrainNormals != NULL)
				glNormal3f(terrainNormals[3*((i+1)*terrainGridWidth + (j+1))],
					   terrainNormals[3*((i+1)*terrainGridWidth + (j+1))+1],
					   terrainNormals[3*((i+1)*terrainGridWidth + (j+1))+2]);
			glTexCoord2f(0.0f, 1.0f);			  
			glVertex3f(
				startW + j + xOffset,
				terrainHeights[(i+1)*terrainGridWidth + (j+1)] + yOffset,
				startL - (i+1) + zOffset);

			if (terrainColors != NULL) 
				glColor3f(terrainColors[3*(i*terrainGridWidth + (j+1))],
					  terrainColors[3*(i*terrainGridWidth + (j+1))+1],
					  terrainColors[3*(i*terrainGridWidth + (j+1))+2]);
			if (terrainNormals != NULL)
				glNormal3f(terrainNormals[3*(i*terrainGridWidth + (j+1))],
					   terrainNormals[3*(i*terrainGridWidth + (j+1))+1],
					   terrainNormals[3*(i*terrainGridWidth + (j+1))+2]);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(
				startW + j + xOffset, 
				terrainHeights[(i)*terrainGridWidth + (j+1)] + yOffset,
				startL - i + zOffset);	
			glDisable(GL_TEXTURE_2D);		
                    }
                    else{                    
		        loadTextures("roca1.jpg");
	                glEnable(GL_TEXTURE_2D);
	                glBindTexture(GL_TEXTURE_2D, texID[0]);	
			if (terrainColors != NULL) 
				glColor3f(terrainColors[3*((i+1)*terrainGridWidth + j)],
					  terrainColors[3*((i+1)*terrainGridWidth + j)+1],
					  terrainColors[3*((i+1)*terrainGridWidth + j)+2]);
			if (terrainNormals != NULL)
				glNormal3f(terrainNormals[3*((i+1)*terrainGridWidth + j)],
					   terrainNormals[3*((i+1)*terrainGridWidth + j)+1],
					   terrainNormals[3*((i+1)*terrainGridWidth + j)+2]);
			glTexCoord2f(0.0f, 0.0f);			  
			glVertex3f(
				startW + j + xOffset,
				terrainHeights[(i+1)*terrainGridWidth + (j)] + yOffset,
				startL - (i+1) + zOffset);

			if (terrainColors != NULL) 
				glColor3f(terrainColors[3*(i*terrainGridWidth + j)],
					  terrainColors[3*(i*terrainGridWidth + j)+1],
					  terrainColors[3*(i*terrainGridWidth + j)+2]);
			if (terrainNormals != NULL)
				glNormal3f(terrainNormals[3*(i*terrainGridWidth + j)],
					   terrainNormals[3*(i*terrainGridWidth + j)+1],
					   terrainNormals[3*(i*terrainGridWidth + j)+2]);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(
				startW + j + xOffset, 
				terrainHeights[(i)*terrainGridWidth + j] + yOffset,
				startL - i + zOffset);		



			if (terrainColors != NULL) 
				glColor3f(terrainColors[3*((i+1)*terrainGridWidth + (j+1))],
					  terrainColors[3*((i+1)*terrainGridWidth + (j+1))+1],
					  terrainColors[3*((i+1)*terrainGridWidth + (j+1))+2]);
			if (terrainNormals != NULL)
				glNormal3f(terrainNormals[3*((i+1)*terrainGridWidth + (j+1))],
					   terrainNormals[3*((i+1)*terrainGridWidth + (j+1))+1],
					   terrainNormals[3*((i+1)*terrainGridWidth + (j+1))+2]);
			glTexCoord2f(0.0f, 1.0f);			  
			glVertex3f(
				startW + j + xOffset,
				terrainHeights[(i+1)*terrainGridWidth + (j+1)] + yOffset,
				startL - (i+1) + zOffset);

			if (terrainColors != NULL) 
				glColor3f(terrainColors[3*(i*terrainGridWidth + (j+1))],
					  terrainColors[3*(i*terrainGridWidth + (j+1))+1],
					  terrainColors[3*(i*terrainGridWidth + (j+1))+2]);
			if (terrainNormals != NULL)
				glNormal3f(terrainNormals[3*(i*terrainGridWidth + (j+1))],
					   terrainNormals[3*(i*terrainGridWidth + (j+1))+1],
					   terrainNormals[3*(i*terrainGridWidth + (j+1))+2]);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(
				startW + j + xOffset, 
				terrainHeights[(i)*terrainGridWidth + (j+1)] + yOffset,
				startL - i + zOffset);
			glDisable(GL_TEXTURE_2D);		
                    }
		}
		glEnd();
	}
	glEndList();
	return(terrainDL);
}

float terrainGetHeight(int x, int z) {

	int xt,zt;

	if (terrainHeights == NULL) 
			return(0.0);

	xt = x + terrainGridWidth /2;
	zt = terrainGridWidth - (z + terrainGridLength /2);

	if ((xt > terrainGridWidth) || (zt > terrainGridLength) || (xt < 0) || (zt < 0))
		return(0.0);

	return(terrainHeights[zt * terrainGridWidth + xt]);
}


void terrainDestroy() {

	if (terrainHeights != NULL)
		free(terrainHeights);

	if (terrainColors != NULL)
		free(terrainColors);

	if (terrainNormals != NULL)
		free(terrainNormals);
}
