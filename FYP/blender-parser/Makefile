CC = clang++
OBJS = main.o parser.o object.o face.o vertex.o material.o vec3.o
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

all: parser

parser: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o parser

main.o: main.cpp parser.h
	$(CC) $(CFLAGS) main.cpp

parser.o: parser.cpp parser.h object.h
	$(CC) $(CFLAGS) parser.cpp

object.o: object.cpp object.h face.h material.h
	$(CC) $(CFLAGS) object.cpp

face.o: face.cpp face.h vertex.h
	$(CC) $(CFLAGS) face.cpp

vertex.o: vertex.cpp vertex.h vec3.h
	$(CC) $(CFLAGS) vertex.cpp

material.o: material.cpp material.h vec3.h
	$(CC) $(CFLAGS) material.cpp

vec3.o: vec3.cpp vec3.h includes.h
	$(CC) $(CFLAGS) vec3.cpp

clean:
	rm *.o parser