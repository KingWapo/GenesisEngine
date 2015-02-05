CPP_SRC  = example1.cpp example2.cpp example3.cpp example4.cpp example5.cpp
GLT_HOME = ../../..
INCLUDE  = -I$(GLT_HOME)/src/glui
GLT_LIBS = -L$(GLT_HOME)/lib -lglui

ifdef WINDIR
LIBS     = $(GLT_LIBS) -lglut32 -lglu32 -lopengl32
else
LIBS     = $(GLT_LIBS) -L/usr/X11R6/lib -lglut -lGLU -lGL -lX11 -lXmu
endif

default: prog

include $(GLT_HOME)/gcc/Makefile.inc
