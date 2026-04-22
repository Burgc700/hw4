CC = mpicc
CFLAGS = -Wall -Wextra -O2
TARGET = pt2

all: $(TARGET)

$TARGET: pt2.c
	$(CC) $(CFLAGS) -o $(TARGET) pt2.c
clean:
	rm -f $(TARGET) *.o 