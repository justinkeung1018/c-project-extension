CC      ?= gcc
CFLAGS  ?= -std=c17 -g\
	-D_POSIX_SOURCE -D_DEFAULT_SOURCE\
	-Wall -Werror -pedantic\
	-I../raylib/src -I..
LDLIBS = -L../raylib/src -lraylib -lm

.SUFFIXES: .c .o

.PHONY: all clean

all: src test

test: test.o test_collision.o ../collision.o

test_collision.o: test_collision.h

src:
	cd ../; make

clean:
	$(RM) *.o test;
	cd ../; make clean
