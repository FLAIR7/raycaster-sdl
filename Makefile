build:
	gcc main.c -lm -lSDL2 -o main

run:
	./main

clean:
	rm -rf main
