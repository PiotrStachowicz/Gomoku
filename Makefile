
output: Gomoku.o
	gcc -Wall -Wextra -O3 Gomoku.c -o output

Gomoku.o: Gomoku.c header.h
	gcc -Wall -Wextra -O3 -c Gomoku.c

clean:
	rm *.o output