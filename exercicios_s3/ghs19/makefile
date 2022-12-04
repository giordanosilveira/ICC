CC=gcc
CFLAGS=-Wall -g
CLIBS=-lm
executavel=solucoesEquacoesDiferenciais
objs=solucoesEquacoesDiferenciais.o

all: $(executavel)

$(executavel): $(objs)
	$(CC) -o $(executavel) $^ $(CFLAGS) -lm

clean:
	rm -f *.o *.bak

purge: clean
	rm -f $(executavel)
