CC = g++
OBJS = parser.o vec3.o main.o object.o
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

object.o: object.cpp object.h face.h
	$(CC) $(CFLAGS) object.cpp

vec3.o: vec3.cpp vec3.h
	$(CC) $(CFLAGS) vec3.cpp

clean:
	rm *.o parser