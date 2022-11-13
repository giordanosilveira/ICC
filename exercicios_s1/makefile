CFLAGS=-Wall -g
CC=gcc
executavel=ex1
executavel2=ex2
executavel3=ex3
executavel4=ex4

all: $(executavel) $(executavel2) $(executavel3) $(executavel4)


$(executavel4): ex4.o
	$(CC) $(CFLAGS) -o $(executavel4) ex4.o -lm

$(executavel3): ex3.o
	$(CC) $(CFLAGS) -o $(executavel3) ex3.o -lm

$(executavel2): ex2.o
	$(CC) $(CFLAGS) -o $(executavel2) ex2.o

$(executavel): ex1.o
	$(CC) $(CFLAGS) -o $(executavel) ex1.o

ex4.o: ex4.c
	$(CC) -c $(CFLAGS) ex4.c -lm

ex3.o: ex3.c
	$(CC) -c $(CFLAGS) ex3.c -lm

ex2.o: ex2.c
	$(CC) -c $(CFLAGS) ex2.c

ex1.o: ex1.c
	$(CC) -c $(CFLAGS) ex1.c

clean:
	rm -f *.o

purge: clean
	rm -f $(executavel) $(executavel2) $(executavel3) $(executavel4)