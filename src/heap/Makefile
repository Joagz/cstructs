SRCS	= ./heap.c
BINS	= ./bin/heap
OBJS	= ./build/heap.o
FLAGS	= -g -Wall

all: $(OBJS)
	gcc $(FLAGS) $(OBJS) -o $(BINS)

$(OBJS): $(SRCS)
	gcc -c $(SRCS) $(FLAGS) -o $(OBJS)

clean:
	rm -rf $(OBJS) $(BINS)
