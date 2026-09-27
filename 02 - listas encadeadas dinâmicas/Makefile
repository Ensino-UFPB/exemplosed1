CC     = gcc
CFLAGS = -Wall -Wextra -std=c11

teste: ListaDinEncad.o main.o
	$(CC) $(CFLAGS) -o teste ListaDinEncad.o main.o

ListaDinEncad.o: ListaDinEncad.c ListaDinEncad.h
	$(CC) $(CFLAGS) -c ListaDinEncad.c

main.o: main.c ListaDinEncad.h
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f *.o teste
