CC = gcc
cflags := -g -O3
executables = project2
all: $(executables)
debug: cflags += -DDEBUG 
debug: all

clean:
	$(RM) $(executables)

project2: project2.c
	$(CC) project2.c $(cflags) -o project2
