CC = gcc
CFLAGS = -Wall

all: main

main: main.c
	$(CC) $(CFLAGS) $< -o $@

clean: clean-linux

clean-linux:
	rm -f main.out

clean-windows:
	del main.exe