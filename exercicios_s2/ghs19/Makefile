    CC     = gcc -g
    CFLAGS = -Wall
    LFLAGS = -lm

      PROG = labSisLin
      OBJS = utils.o \
             sislin.o \
             Metodos.o \
             $(PROG).o

.PHONY: limpa faxina clean distclean purge all

%.o: %.c %.h utils.h sislin.h
	$(CC) -c $(CFLAGS) $<

$(PROG):  $(OBJS)
	$(CC) -o $@ $^ $(LFLAGS)

clean:
	@rm -f *~ *.bak *.o

purge:   clean
	@rm -f core a.out
	@rm -f $(PROG)

