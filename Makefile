ifeq ($(OS),Windows_NT) 
    detected_OS := Windows
else
    detected_OS := $(shell sh -c 'uname 2>/dev/null || echo Unknown')
endif

CC=gcc

CFLAGS += -Wall -Wextra -Wpedantic \
          -Wwrite-strings -Wshadow \
          -O2 -g3 -std=c99

all: print build

print:
	@echo OS: $(detected_OS)

build:
	$(CC) $(CFLAGS) ./src/*.c -lm -lSDL2 -lSDL2_image -o raycast

run:
	./raycast

clean:
	rm -rf raycast
