CC     = gcc
CFLAGS = -Wall -Wextra -std=c11

teste: ListaSequencial.o main.o
	$(CC) $(CFLAGS) -o teste ListaSequencial.o main.o

ListaSequencial.o: ListaSequencial.c ListaSequencial.h
	$(CC) $(CFLAGS) -c ListaSequencial.c

main.o: main.c ListaSequencial.h
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f *.o teste
