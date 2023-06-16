CC      ?= gcc
CFLAGS  ?= -std=c17 -g\
	-D_POSIX_SOURCE -D_DEFAULT_SOURCE\
	-Wall -Werror -pedantic\
	-Iraylib/src
LDLIBS  = -Lraylib/src -lraylib -lm

.SUFFIXES: .c .o

.PHONY: all clean

all: main

main: main.o spaceship.o asteroids.o bullet.o list.o

asteroids.o: asteroids.h list.h
bullet.o: bullet.h list.h
spaceship.o: spaceship.h list.h

clean:
	$(RM) *.o main
