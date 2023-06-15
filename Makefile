CC      ?= gcc
CFLAGS  ?= -std=c17 -g\
	-D_POSIX_SOURCE -D_DEFAULT_SOURCE\
	-Wall -Werror -pedantic\
	-Iraylib/src
LDLIBS  = -Lraylib/src -lraylib -lm

.SUFFIXES: .c .o

.PHONY: all clean

all: main

main: main.o asteroids.o dynarr.o bullet.o

asteroids.o: dynarr.o
bullet.o: dynarr.o

clean:
	$(RM) *.o main asteroids
