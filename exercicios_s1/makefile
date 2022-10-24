CFLAGS=-Wall -g
CC=gcc
executavel=ex1

all: $(executavel)

$(executavel): ex1.o
	$(CC) $(CFLAGS) -o $(executavel) ex1.o

ex1.o: ex1.c
	$(CC) -c $(CFLAGS) ex1.c

clean:
	rm -f *.o

purge: clean
	rm $(executavel)