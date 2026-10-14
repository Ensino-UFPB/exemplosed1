CC     = gcc
CFLAGS = -Wall -Wextra -std=c11

teste: ListaDinEncadCirc.o main.o
	$(CC) $(CFLAGS) -o teste ListaDinEncadCirc.o main.o

ListaDinEncadCirc.o: ListaDinEncadCirc.c ListaDinEncadCirc.h
	$(CC) $(CFLAGS) -c ListaDinEncadCirc.c

main.o: main.c ListaDinEncadCirc.h
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f *.o teste
