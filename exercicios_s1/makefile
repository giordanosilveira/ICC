CFLAGS=-Wall -g
CC=gcc
executavel=ex1
executavel2=ex2

all: $(executavel)
exercicio2: $(executavel2) 

$(executavel2): ex2.o
	$(CC) $(CFLAGS) -o $(executavel2) ex2.o

$(executavel): ex1.o
	$(CC) $(CFLAGS) -o $(executavel) ex1.o

ex2.o: ex2.c
	$(CC) -c $(CFLAGS) ex2.c

ex1.o: ex1.c
	$(CC) -c $(CFLAGS) ex1.c

clean:
	rm -f *.o

purge: clean
	rm $(executavel)