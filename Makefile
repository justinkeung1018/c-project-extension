CC      ?= gcc
CFLAGS  ?= -std=c17 -g\
	-D_POSIX_SOURCE -D_DEFAULT_SOURCE\
	-Wall -Werror -pedantic\
	-Iraylib/src
LDLIBS  = -Lraylib/src -lraylib -lm

.SUFFIXES: .c .o

.PHONY: all clean

all: main test

main: main.o

test: test.o

clean:
	$(RM) *.o main

