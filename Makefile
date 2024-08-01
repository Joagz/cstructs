CC=gcc

BIN_FOLDER=./bin
BUILD_FOLDER=./build 
SRC_FOLDER=./src 

MAIN_SRC=./src/main.c 
MAIN_O=./build/main.o 
MAIN=./bin/main

DYNAMIC_ARRAY_SRC=./src/darr/darr.c
DYNAMIC_ARRAY_O=./build/darr/darr.o 

LINKED_LIST_SRC=./src/linkedlist/linkedlist.c
LINKED_LIST_O=./build/linkedlist/linkedlist.o

QUEUE_SRC = ./src/queue/queue.c
QUEUE_O = ./build/queue/queue.o

FILES = $(DYNAMIC_ARRAY_O) $(LINKED_LIST_O) $(QUEUE_O)
INCLUDES = -I./src/ 

all: $(FILES)
	$(CC) $(MAIN_SRC) $(FILES) $(INCLUDES) -o $(MAIN)

$(DYNAMIC_ARRAY_O): $(DYNAMIC_ARRAY_SRC)
	$(CC) -c $(DYNAMIC_ARRAY_SRC) -I./src/darr/ -I./src/ -o $(DYNAMIC_ARRAY_O)

$(LINKED_LIST_O): $(LINKED_LIST_SRC)
	$(CC) -c $(LINKED_LIST_SRC) -I./src/linkedlist/ -I./src/ -o $(LINKED_LIST_O)


$(QUEUE_O): $(QUEUE_SRC)
	$(CC) -c $(QUEUE_SRC) -I./src/linkedlist/ -I./src/queue/ -I./src/ -o $(QUEUE_O)


clean:
	rm -rf ./build/main.o
	rm -rf $(FILES)
