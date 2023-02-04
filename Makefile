output: board.o patterns.o game_ai.o Gomoku.o
	gcc -Wall -Wextra -O3 board.o patterns.o game_ai.o Gomoku.o -o output

board.o: board.c header.h
	gcc -Wall -Wextra -O3 -c board.c -o board.o

patterns.o: patterns.c header.h
	gcc -Wall -Wextra -O3 -c patterns.c -o patterns.o

game_ai.o: game_ai.c header.h
	gcc -Wall -Wextra -O3 -c game_ai.c -o game_ai.o

Gomoku.o: Gomoku.c header.h
	gcc -Wall -Wextra -O3 -c Gomoku.c -o Gomoku.o

clean:
	rm *.o output