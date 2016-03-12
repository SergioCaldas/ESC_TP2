all: trap_busy trap_mutex trap_sem


trap_busy : busy.c
	gcc -Wall -o trap_busy busy.c trapezoide.c -lpthread

trap_mutex : mutex.c
	gcc -Wall -o trap_mutex mutex.c trapezoide.c -lpthread

trap_sem : semaphore.c
	gcc -Wall -o trap_sem semaphore.c trapezoide.c -lpthread

.PHONY: clean

clean:
	rm -f *.o
	rm -f *.out
	rm -f trap_*
