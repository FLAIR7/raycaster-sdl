CC=gcc

build:
	$(CC) -Wall -Wextra -pedantic -std=c99 -O2  main.c -lm -lSDL2 -o main

run:
	./main

clean:
	rm -rf main
