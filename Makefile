
EXEC := graph
SRC := ./src
INC := ./inc

CPP := g++
CXX := ${CPP}
CC := ${CPP}
#CPPFLAGS := -ggdb -I${INC}
#LFLAGS :=
#LIBS := -lrt
FLAGS := -Wall -ggdb -I${INC}

UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)
CPPFLAGS := ${FLAGS} -D__MAC__
LIBS := -framework OpenGL -framework GLUT -lpthread -lpng
else
CPPFLAGS := ${FLAGS}
LIBS := -lglut -lGLU -lGL -lpthread -lm -lpng
endif

LINKFLAGS := -Wall
CFLAGS := ${CPPFLAGS}

OBJECTS := $(patsubst %.cpp, %.o, $(wildcard ${SRC}/*.cpp))

.PHONEY: all clean

all: ${EXEC}

clean:
	rm -f ${SRC}/*.o ${EXEC}

${EXEC}: ${OBJECTS}
	${CPP} ${LINKFLAGS} -o ${EXEC} ${OBJECTS} ${LIBS}
