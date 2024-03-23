CC = gcc
CFLAGS = -Wall -g

test_TestServerGTK: test_TestServerGTK.o 
	$(CC) $(CFLAGS) -o test_TestServerGTK test_TestServerGTK.o

test_TestServerGTK.o: test_TestServerGTK.c 
	$(CC) $(CFLAGS) -c test_TestServerGTK.c

clean: 
	rm -f *.o
	rm -f test_TestServerGTK 