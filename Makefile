CC=gcc

CFLAGS += -Wall -Wextra -Wpedantic \
          -Wwrite-strings -Wshadow \
          -O2 -std=c99

build:
	$(CC) $(CFLAGS) ./src/*.c -lm -lSDL2 -o raycast

run:
	./main

clean:
	rm -rf main
