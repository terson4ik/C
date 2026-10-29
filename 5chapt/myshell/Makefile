OBJMODULS = my_string.o parser.o shell_engine.o vector.o word_list.o
CFLAGS = -Wall -g
EXE = shell2
CC = gcc

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

$(EXE): main.c $(OBJMODULS)
	$(CC) $(CFLAGS) $^ -o $@

build: $(EXE)


run: $(EXE)
	./$(EXE)

clean:
	rm -f *.o $(EXE)
