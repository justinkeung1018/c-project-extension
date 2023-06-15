CC      ?= gcc
CFLAGS  ?= -std=c17 -g\
	-D_POSIX_SOURCE -D_DEFAULT_SOURCE\
	-Wall -Werror -pedantic\
	-Iraylib/src
LDLIBS  = -Lraylib/src -lraylib -lm

.SUFFIXES: .c .o

.PHONY: all clean

all: main

main: main.o spaceship.o asteroids.o dynarr.o

asteroids.o: dynarr.o

spaceship.o: spaceship.h

clean:
	$(RM) *.o main
