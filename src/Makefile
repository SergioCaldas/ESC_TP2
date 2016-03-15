all: pth_hello trap_busy trap_mutex trap_sem

pth_hello: pth_hello.c
	gcc-5 -Wall -o pth_hello pth_hello.c -lpthread

trap_busy : busy.c
	gcc-5 -Wall -o trap_busy busy.c trapezoide.c -lpthread

trap_mutex : mutex.c
	gcc-5 -Wall -o trap_mutex mutex.c trapezoide.c -lpthread

trap_sem : semaphore.c
	gcc-5 -Wall -o trap_sem semaphore.c trapezoide.c -lpthread

.PHONY: clean

clean:
	rm -f *.o
	rm -f *.out
	rm -f trap_*
	rm -rf CSV/
	rm -f pth_hello
