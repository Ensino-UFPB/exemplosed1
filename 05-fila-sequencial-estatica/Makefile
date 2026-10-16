CC     = gcc
CFLAGS = -Wall -Wextra -std=c11

teste: FilaEstatica.o main.o
	$(CC) $(CFLAGS) -o teste FilaEstatica.o main.o

FilaEstatica.o: FilaEstatica.c FilaEstatica.h
	$(CC) $(CFLAGS) -c FilaEstatica.c

main.o: main.c FilaEstatica.h
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f *.o teste
