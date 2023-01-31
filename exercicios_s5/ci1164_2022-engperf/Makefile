PROG   = matmult

CC = gcc -g
OBJS = matriz.o

CFLAGS = -I${LIKWID_INCLUDE} -DLIKWID_PERFMON
LFLAGS = -lm 
LIKWIDFLAGS = -L${LIKWID_LIB} -llikwid 


.PHONY: all debug clean limpa purge faxina

%.o: %.c %.h
	$(CC) $(CFLAGS) -O3 -mavx2 -march=native -c $<

all: $(PROG)

debug:         CFLAGS += -DDEBUG
debug:         $(PROG)

$(PROG):  $(PROG).o

$(PROG): $(OBJS) 
	$(CC) $(CFLAGS) -O3 -mavx2 -march=native -o $@ $^ $(LFLAGS) $(LIKWIDFLAGS)

clean limpa:
	@echo "Limpando ...."
	@rm -f *~ *.bak *.tmp *.o

purge faxina:   clean
	@echo "Faxina ...."
	@rm -f  $(PROG) core a.out
	@rm -f *.png marker.out *.log *.csv
