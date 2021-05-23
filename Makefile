all:
	gcc threads/CEthread.c threads/steque.c ants.c scheduler.c -o ant -lm -lrt
