CC=gcc
CFLAGS=-c -Wall

all: run

run: main.o funcoes.o salvar.o
	$(CC) main.o funcoes.o salvar.o -o run

main.o: main.c
	$(CC) $(CFLAGS) main.c

funcoes.o: funcoes.c
	$(CC) $(CFLAGS) funcoes.c

salvar.o: salvar.c
	$(CC) $(CFLAGS) salvar.c

clean:
	rm -rf *.o run
