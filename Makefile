CC      ?= gcc
CFLAGS  ?= -std=c17 -g\
	-D_POSIX_SOURCE -D_DEFAULT_SOURCE\
	-Wall -Werror -pedantic\
	-Iraylib/src
LDLIBS  = -Lraylib/src -lraylib -lm

.SUFFIXES: .c .o

.PHONY: all clean

all: main

main: main.o spaceship.o asteroid.o bullet.o list.o collision.o loading.o player.o

asteroid.o: asteroid.h list.h
bullet.o: bullet.h list.h
collision.o: asteroid.h spaceship.h
player.o: player.h
spaceship.o: spaceship.h list.h utils.h

clean:
	$(RM) *.o main

