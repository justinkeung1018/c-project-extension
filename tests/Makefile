CC      ?= gcc
CFLAGS  ?= -std=c17 -g\
	-D_POSIX_SOURCE -D_DEFAULT_SOURCE\
	-Wall -Werror -pedantic\
	-I.. -I../raylib/src
LDLIBS = -L../raylib/src -lraylib -lm

.SUFFIXES: .c .o

.PHONY: all clean

all: src test

test: test.o test_collision.o test_utils.o ../collision.o ../spaceship.o ../list.o ../bullet.o

test_collision.o: test_collision.h test_utils.h
test_utils.o: test_utils.h

src:
	cd ../; make

clean:
	$(RM) *.o test;
	cd ../; make clean
