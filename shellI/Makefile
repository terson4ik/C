FLAGS = -pedantic -Wall -g 
OBJMODULS = extraIO.o  main.o word_list.o
EXE = shell1

%.o: %.c  # without headers
	$(CC) $(FLAGS) -c $< -o $@

%.o: %.c %.h
	$(CC) $(FLAGS) -c $< -o $@

prog: $(OBJMODULS)
	$(CC) $(FLAGS) $^ -o prog

run: $(EXE)
	./$(EXE)

build: $(EXE)

clean:
	rm -f $(EXE) *.o
