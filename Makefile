CC      ?= gcc
CFLAGS  ?= -std=c17 -g\
	-D_POSIX_SOURCE -D_DEFAULT_SOURCE\
	-Wall -Werror -pedantic\
	-Iraylib/src
LDLIBS  = -Lraylib/src -lraylib -lm

.SUFFIXES: .c .o

.PHONY: all clean

all: main

main: main.o asteroids.o dynarr.o bullet.o spaceship.o

asteroids.o: asteroids.h dynarr.h
bullet.o: bullet.h dynarr.h

spaceship.o: spaceship.h bullet.h dynarr.h

clean:
	$(RM) *.o main asteroids
