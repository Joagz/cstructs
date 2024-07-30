CC=gcc

BIN_FOLDER=./bin
BUILD_FOLDER=./build 
SRC_FOLDER=./src 

MAIN_SRC=./src/main.c 
MAIN_O=./build/main.o 
MAIN=./bin/main

DYNAMIC_ARRAY_SRC=./src/darr/darr.c
DYNAMIC_ARRAY_O=./build/darr/darr.o 

FILES = $(DYNAMIC_ARRAY_O)
INCLUDES = -I./src/ 

all: $(FILES)
	$(CC) $(MAIN_SRC) $(FILES) $(INCLUDES) -o $(MAIN)

$(DYNAMIC_ARRAY_O): $(DYNAMIC_ARRAY_SRC)
	$(CC) -c $(DYNAMIC_ARRAY_SRC) -I./src/darr/ -I./src/ -o $(DYNAMIC_ARRAY_O)

clean:
	rm -rf ./build/main.o
	rm -rf $(FILES)
