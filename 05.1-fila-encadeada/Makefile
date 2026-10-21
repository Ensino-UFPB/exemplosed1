CC     = gcc
CFLAGS = -Wall -Wextra -std=c11

teste: ListaDinEncad.o FilaEncadeada.o  main.o
	$(CC) $(CFLAGS) -o teste FilaEncadeada.o ListaDinEncad.o main.o

FilaEncadeada.o: FilaEncadeada.c FilaEncadeada.h
	$(CC) $(CFLAGS) -c FilaEncadeada.c

ListaDinEncad.o: ListaDinEncad.c ListaDinEncad.h
	$(CC) $(CFLAGS) -c ListaDinEncad.c

main.o: main.c FilaEncadeada.h ListaDinEncad.h
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f *.o teste
