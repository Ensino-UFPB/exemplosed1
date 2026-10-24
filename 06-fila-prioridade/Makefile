CC     = gcc
CFLAGS = -Wall -Wextra -std=c11

teste: FilaPrioridade.o main.o
	$(CC) $(CFLAGS) -o teste FilaPrioridade.o main.o

FilaPrioridade.o: FilaPrioridade.c FilaPrioridade.h
	$(CC) $(CFLAGS) -c FilaPrioridade.c

main.o: main.c FilaPrioridade.h
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f *.o teste
