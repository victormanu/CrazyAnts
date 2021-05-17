CC = gcc            # default is CC = cc
CFLAGS = -g -Wall   # default is CFLAGS = [blank]
AR = ar -cvq
RANLIB = ranlib
PROJ_DIR = ..
INC_DIR = $(PROJ_DIR)/src
LIB_DIR = $(PROJ_DIR)
CETHREADS_SRC = CEthread.c steque.c
CETHREADS_OBJ = $(patsubst %.c,%.o,$(CETHREADS_SRC))
HEADER = CEthread.h steque.h
LIBRARY = libcethread.a

# pattern rule for object files
%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

all: $(CETHREADS_OBJ) library

library: $(CETHREADS_OBJ)
	$(AR) $(LIB_DIR)/$(LIBRARY) $(CETHREADS_OBJ)
	$(RANLIB) $(LIB_DIR)/$(LIBRARY)       

clean:
	$(RM) -f *.o $(LIB_DIR)/* $(CETHREAD_OBJ)
