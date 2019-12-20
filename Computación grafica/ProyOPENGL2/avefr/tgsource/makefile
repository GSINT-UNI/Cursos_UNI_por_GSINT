
.SUFFIXES: .cpp


#Change the following two lines to reflect the locations
# of the GLUT library (.a) and includes on your system

GLUT_LIB_LOCATION=/usr/X11R6/lib
GLUT_INC_LOCATION=/usr/X11R6/include

CC=g++
CPPFLAGS=-I${GLUT_INC_LOCATION} #-w 
GLLIBS=-L${GLUT_LIB_LOCATION} -lglut -lGL -lGLU
LPATH=${GLUTPATH} 
INCS= 


libs =     ${GLLIBS}   -lm  


All: terrain 


terrain: tg.o tga.o terrain.o 
	$(CC)   $(LPATH) tg.o tga.o terrain.o /usr/lib/libglui.a $(libs) -o terrain


.cpp.o:
	$(CC) -c -D_LINUX_ $(INCS) $*.cpp

clean:
	rm *.o

tg.o: tg.cpp terrain.h tga.h glui.h 
tga.o: tga.cpp tga.h
terrain.o : terrain.cpp terrain.h

