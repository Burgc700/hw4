CC = gcc
CFLAGS = -Wall -Wextra -O2 -pthread
TARGET = pt1

all: $(TARGET)

$TARGET: pt1.c
	$(CC) $(CFLAGS) -o $(TARGET) pt1.c
clean:
	rm -f $(TARGET) *.o 