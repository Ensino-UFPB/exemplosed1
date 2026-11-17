CC     = gcc
CFLAGS = -Wall -Wextra -std=c11

teste: Grafo.o main.o
	$(CC) $(CFLAGS) -o teste Grafo.o main.o

Grafo.o: Grafo.c Grafo.h
	$(CC) $(CFLAGS) -c Grafo.c

main.o: main.c Grafo.h
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f *.o teste
