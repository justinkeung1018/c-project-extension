CC      ?= gcc
CFLAGS  ?= -std=c17 -g\
	-D_POSIX_SOURCE -D_DEFAULT_SOURCE\
	-Wall -Werror -pedantic\
	-I.. -I../raylib/src
LDLIBS = -L../raylib/src -lraylib -lm

.SUFFIXES: .c .o

.PHONY: all clean

all: src test

test: test.o test_asteroid.o test_collision.o test_spaceship.o test_bullet.o test_utils.o test_list.o ../collision.o ../spaceship.o ../list.o ../bullet.o ../asteroid.o

test_asteroid: test_asteroid.h test_utils.h
test_bullet.o: test_bullet.h test_utils.h
test_collision.o: test_collision.h test_utils.h
test_spaceship.o: test_spaceship.h test_utils.h
test_list.o: test_list.h test_utils.h
test_utils.o: test_utils.h

src:
	cd ../; make

clean:
	$(RM) *.o test;
	cd ../; make clean
