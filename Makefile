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

## COMPILATION FLAGS ##

# These FLAGS are important for the correct execution of this library.
# SYS_TYPE flag must be defined and represents the address space 
# of the system running this library, here is a list with each acceptable
# value:
#
# 
#	SYS_TYPE		address space
# 0x01				64-bit
# 0x02        32-bit 
# 0x03        16-bit
#
# 32 bit is used as fallback if you set an incorrect value, however, this
# library will not run if SYS_TYPE is not defined 

FLAGS = -DSYS_TYPE=1 -Werror -Wall 

## END OF COMPILATION FLAGS ##


all: $(FILES)
	$(CC) $(MAIN_SRC) $(FLAGS) $(FILES) $(INCLUDES) -o $(MAIN)

$(DYNAMIC_ARRAY_O): $(DYNAMIC_ARRAY_SRC)
	$(CC) -c $(DYNAMIC_ARRAY_SRC) $(FLAGS) -I./src/darr/ -I./src/ -o $(DYNAMIC_ARRAY_O)

$(LINKED_LIST_O): $(LINKED_LIST_SRC)
	$(CC) -c $(LINKED_LIST_SRC) $(FLAGS) -I./src/linkedlist/ -I./src/ -o $(LINKED_LIST_O)


$(QUEUE_O): $(QUEUE_SRC)
	$(CC) -c $(QUEUE_SRC) $(FLAGS) -I./src/linkedlist/ -I./src/queue/ -I./src/ -o $(QUEUE_O)


clean:
	rm -rf ./build/main.o
	rm -rf $(FILES)
