CC     = gcc
CFLAGS = -Wall -Wextra -std=c11

teste: PilhaSequencial.o main.o
	$(CC) $(CFLAGS) -o teste PilhaSequencial.o main.o

PilhaSequencial.o: PilhaSequencial.c PilhaSequencial.h
	$(CC) $(CFLAGS) -c PilhaSequencial.c

main.o: main.c PilhaSequencial.h
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f *.o teste
