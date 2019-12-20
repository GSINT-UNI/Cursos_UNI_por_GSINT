CXXFLAGS=-ggdb
LDLIBS=-lglut -lGLEW -lGL -lm -I ./ -I ./glm
all: obj-viewer
obj-viewer: ../common/shader_utils.o
clean:
	rm -f *.o obj-viewer

.PHONY: all clean
