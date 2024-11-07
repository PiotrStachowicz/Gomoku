CC = gcc

CFLAGS = -Wall -O3 -Wextra

SRCS = board/board.c computer/evaluation/eval.c computer/computer.c

OBJS = $(SRCS:.c=.o)

TARGET = gomoku

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
