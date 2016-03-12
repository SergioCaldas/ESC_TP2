all: pth_hello trap_busy trap_mutex trap_sem

pth_hello : pth_hello.c
	gcc-5 -Wall -o pth_hello pth_hello.c -lpthread

trap_busy : trap.c
	gcc-5 -Wall -DD_BUSYWAITING -o trap_busy trap.c -lpthread

trap_mutex : trap.c
	gcc-5 -Wall -DD_MUTEX -o trap_mutex trap.c -lpthread

trap_sem : trap.c
	gcc-5 -Wall -DD_SEMAPHORE -o trap_sem trap.c -lpthread

.PHONY: clean

clean:
	rm -f *.o
	rm -f *.out
	rm -rf CSV/
	rm -f pth_hello
	rm -f trap_*
