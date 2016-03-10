all: busy mutex semaphore

busy : busy.c
	gcc-5 -Wall -o busy busy.c trapezoide.c -lpthread

mutex : mutex.c
	gcc-5 -Wall -o mutex mutex.c trapezoide.c -lpthread

semaphore : semaphore.c
	gcc-5 -Wall -o semaphore semaphore.c trapezoide.c -lpthread

.PHONY: clean

clean:
	rm -f *.o
	rm -f *.out
	rm -f busy
	rm -f mutex
	rm -f semaphore
