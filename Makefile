all:
	gcc threads/CEthread.c threads/steque.c ants.c -o ant -lm -lrt
