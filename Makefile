CC=gcc

CFLAGS += -Wall -Wextra -Wpedantic \
          -Wwrite-strings -Wshadow \
          -O2 -std=c99

build:
	$(CC) $(CFLAGS) main.c -lm -lSDL2 -o main

run:
	./main

clean:
	rm -rf main
