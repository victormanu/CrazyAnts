all:
	gcc threads/CEthread.c threads/steque.c ants.c scheduler.c canal.c -o ant -lm -lrt
