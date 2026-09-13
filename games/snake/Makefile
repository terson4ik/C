CFLAGS = -Wall -ansi -pedantic 

tui.o: tui.c tui.h common_types.h
	$(CC) $(CFLAGS) -c $< -lncurses -o tui.o

snake.o: snake.c snake.h common_types.h
	$(CC) $(CFLAGS) -c $< -lncurses -o snake.o

snake: main.c tui.o snake.o common_types.h
	$(CC) $(CFLAGS) $^ -lncurses -o snake

run: snake
	./snake

clean:
	rm -f *.o snake
