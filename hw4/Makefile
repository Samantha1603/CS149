CC=gcc
HDIR=./include
CFLAGS=-I$(HDIR)	-std=c99	-g
makehw4:	main.o	process_operations.o
	$(CC)	$(CFLAGS)	-o	hw4	main.o process_operations.o
clean:
	rm *.o hw4 *.stackdump