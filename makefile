CC = gcc
cflags := -g -O3 -Wall
executables = project2
sources = firstFit.c  $(executables).c
headers = firstFit.h Util.h project2.h
all:$(executables)
debug: cflags += -DDEBUG 
debug: all

clean:
	$(RM) $(executables)
	$(RM) $(dependancies).o

project2: ${sources}
	$(CC) $(sources) -o project2

