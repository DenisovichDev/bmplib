CC=gcc
CFLAGS=-Wall -g

all: example

example: main.o bmp.o
	$(CC) $(CFLAGS) $^

%.o: %.c
	$(CC) $(CFLAGS) -c $^

clean:
	rm -f *.o example *.out a
