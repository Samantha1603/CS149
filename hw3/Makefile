CC=gcc
OS=$(shell uname)
HDIR=./include
LDIR=./lib
ifeq ($(OS),MINGW32_NT-6.2)
CFLAGS=-I$(HDIR)	-std=c99	-DHAVE_STRUCT_TIMESPEC	-g
LDFLAGS=-lpthreadGC2
makeHW3:	main.o	seller.o	customer.o 	algorithms.o
	$(CC)	$(CFLAGS)	-o	main main.o	seller.o	algorithms.o 	customer.o	$(LDFLAGS)
else
CFLAGS=-I$(HDIR)	-std=c99	-g
LDFLAGS=-lpthread
makeHW3:	main.o	seller.o	algorithms.o	customer.o	
	$(CC)	$(CFLAGS) $(LDFLAGS)	-o	main	main.o	seller.o	algorithms.o	customer.o 	$(LDFLAGS)
endif
clean:
	rm	-f	*.o	main makeHW3	*.exe
