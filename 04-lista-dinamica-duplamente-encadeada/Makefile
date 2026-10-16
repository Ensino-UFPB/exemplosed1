CC     = gcc
CFLAGS = -Wall -Wextra -std=c11

teste: ListaDinEncadDupla.o main.o
	$(CC) $(CFLAGS) -o teste ListaDinEncadDupla.o main.o

ListaDinEncadDupla.o: ListaDinEncadDupla.c ListaDinEncadDupla.h
	$(CC) $(CFLAGS) -c ListaDinEncadDupla.c

main.o: main.c ListaDinEncadDupla.h
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f *.o teste
