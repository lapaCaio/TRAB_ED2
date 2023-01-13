CC = mingw32-gcc
OBJS = main.o funcoes.o salvar.o

run: $(OBJS)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) -c -o $@ $<

.PHONY: clean
clean:
	mingw32-rm $(OBJS) run
