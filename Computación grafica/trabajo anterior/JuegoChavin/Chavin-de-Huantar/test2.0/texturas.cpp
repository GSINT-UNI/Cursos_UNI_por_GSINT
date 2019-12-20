#include "GL/glut.h"
#include <FreeImage.h>
#include <math.h>

#define DIM 15
#define PI 3.141592

#define numTEXT 11

GLuint texID[numTEXT];
char* textureFileNames[numTEXT] = {"escalon.jpg","cielo.jpeg","box.jpg","pastito.jpeg", "madera.jpeg","pared_blanca.jpeg","piedras1.jpeg","piedras2.jpeg","terror1.jpeg","terror2.jpeg","rehen.jpeg"};

//Cargando Texturas
void loadTextures() {
  int i;
  glGenTextures(numTEXT,texID);  // Obtener el Id textura
  for (i = 0; i < numTEXT; i++) {
     void* imgData;      // Puntero a data del Archivo
     int imgWidth;   // Ancho de Imagen
     int imgHeight;  // Alto de Imagen
     FREE_IMAGE_FORMAT format = FreeImage_GetFIFFromFilename(textureFileNames[i]);
     if (format == FIF_UNKNOWN) {
        //printf("Archivo de Imagen desconocido %s\n", textureFileNames[i]);
            continue;
        }
     FIBITMAP* bitmap = FreeImage_Load(format, textureFileNames[i], 0);  //Leer Imagen
     if (!bitmap) {
        //printf("Fallo la carga de imagen %s\n", textureFileNames[i]);
        continue;
     }
     FIBITMAP* bitmap2 = FreeImage_ConvertTo24Bits(bitmap);  // Convierte a RGB
     FreeImage_Unload(bitmap);
     imgData = FreeImage_GetBits(bitmap2);
     imgWidth = FreeImage_GetWidth(bitmap2);
     imgHeight = FreeImage_GetHeight(bitmap2);
     if (imgData) {
         //printf("Texture cargada %s, tamanio %dx%d\n",textureFileNames[i], imgWidth, imgHeight);
         int format; // Formato del color.
         if ( FI_RGBA_RED == 0 )
            format = GL_RGB;
         else
            format = GL_BGR;
            glBindTexture( GL_TEXTURE_2D, texID[i] );  // Cargando textura
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgWidth, imgHeight, 0, format,GL_UNSIGNED_BYTE, imgData);
              glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        }
        else {
            //printf("Fallo la carga de textura %s\n", textureFileNames[i]);
        }
    }
}
