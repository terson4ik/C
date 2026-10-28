EXE = shell1
CC = gcc
OBJMODULS = my_string.o parser.o shell_engine.o vector.o word_list.o
CFLAGS = -Wall -g

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

$(EXE): main.c $(OBJMODULS)
	$(CC) $(CFLAGS) $^ -o $@

run: $(EXE)
	./$(EXE)

clean:
	rm -f *.o
