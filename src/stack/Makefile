
all: ./bin/stack

./build/stack.o: ./stack.c
	gcc -c ./stack.c -o ./build/stack.o

./bin/stack: ./build/stack.o
	gcc ./build/stack.o -o ./bin/stack

clean:
	rm -rf ./build/stack.o ./bin/stack

