CFLAGS=-Wall -g
CC=gcc
executavel=ex1
executavel2=ex2
executavel3=ex3

all: $(executavel)
exercicio2: $(executavel2) 
exercicio3: $(executavel3)

$(executavel3): ex3.o
	$(CC) $(CFLAGS) -o $(executavel3) ex3.o

$(executavel2): ex2.o
	$(CC) $(CFLAGS) -o $(executavel2) ex2.o

$(executavel): ex1.o
	$(CC) $(CFLAGS) -o $(executavel) ex1.o

ex3.o: ex3.c
	$(CC) -c $(CFLAGS) ex3.c

ex2.o: ex2.c
	$(CC) -c $(CFLAGS) ex2.c

ex1.o: ex1.c
	$(CC) -c $(CFLAGS) ex1.c

clean:
	rm -f *.o

purge: clean
	rm $(executavel)