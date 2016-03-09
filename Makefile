CC=gcc-5
CFLAGS= -Wall -lpthread
DEPS = trapezoide.h
OBJ = pt_trap.o trapezoidal.o

%.o: %.c $(DEPS)
		$(CC) -c -o $@ $< $(CFLAGS)

pt_trap: $(OBJ)
		gcc-5 -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
		rm -f *.o
		rm -f *.out
