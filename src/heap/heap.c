/* min heap */
#include "heap.h"
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#define DEBUG 0
#define HEAP_SIZE_LEVEL1 128
#define HEAP_SIZE_LEVEL2 512
#define HEAP_SIZE_LEVEL3 1024
#define HEAP_SIZE_LEVEL4 2048
#define HEAP_SIZE_LEVEL5 4096
#define HEAP_SIZE_DEFAULT 64

typedef struct {
	size_t size;
	size_t n;
	int *values;
} heap_t;

/* heap internals */
heap_t * heap_init() {
	heap_t * heap 	= (heap_t*)malloc(sizeof(heap_t));
	heap->values 	= (int*)calloc(sizeof(int), HEAP_SIZE_DEFAULT);
	heap->size 	= HEAP_SIZE_DEFAULT;
	heap->n		= 0;

#ifdef DEBUG
	printf("DEBUG: heap alloc \t%p\n", (void*)heap);
#endif

	return heap;
}

heap_t * nheap_init(size_t size)
{
	if(size <= 0)
	{
		printf("HEAP ERROR: Please provide a valid value for heap size (must be > 0)\n");
#ifdef ENABLE_EXIT_ON_HEAP_ERROR
		printf("HEAP ERROR: exiting with code -1\n");
		exit(-1);
#endif
		return 0;
	}
	heap_t * heap	= (heap_t*)malloc(sizeof(heap_t));
	heap->values 	= (int*)calloc(sizeof(int), size);
	heap->size	= size;
	heap->n		= 0;
	return heap;
}

void check_null_and_exit(void* ptr, char* msg)
{
	if(ptr == NULL)
	{
		printf("check_null_and_exit() found a null value...\n");
		printf("-> %s\n", msg);
		exit(-1);
	}
}

/* Resize the current heap values array, adding half the current size */
heap_t *resize(heap_t *ptr)
{

#ifdef DEBUG
	printf("DEBUG: resizing heap (%zu -> %zu)\n", ptr->size, ptr->size + ptr->size/2);
#endif

	ptr->values = realloc(ptr->values, sizeof(int)*(ptr->size + ptr->size/2));
	check_null_and_exit(ptr->values, "resize() heap error");
	return ptr;
}

/*
	add a % of the current size to the current capacity of heap items array.
	for example: if percentage = 50, then the final size value will be the current
	size + half the size (size + size/2).
*/
heap_t *nresize(heap_t *ptr, int percentage)
{

#ifdef DEBUG
	printf("DEBUG: (nresize) resizing heap (%zu -> %zu)", ptr->size, ptr->size + ptr->size * percentage/100);
#endif

	ptr->values = realloc(ptr->values, sizeof(int)*(ptr->size + ptr->size*(percentage/100)));
	check_null_and_exit(ptr->values, "nresize() heap error");
	return ptr;
}

void heapfree(heap_t *ptr)
{
#ifdef DEBUG
	printf("DEBUG: heap free \t%p\n", (void*)ptr);
#endif
	if(ptr != NULL){
		if(ptr->values != NULL) free(ptr->values);
		free(ptr);
	}
}

int getparenti(heap_t *heap, int index)
{
	if(index == 0) return 0;
	return (index-1)/2;
}

int getchildi_l(heap_t *heap, int index)
{
	if(2*index+1 >= heap->n) return index;
	return 2*index+1;
}

int getchildi_r(heap_t *heap, int index)
{
        if(2*index+2 >= heap->n) return getchildi_l(heap, index);
        return 2*index+2;
}

/* heap interface */

/* decides how to resize the heap considering its value */
heap_t * heapresize(heap_t *ptr)
{
	if(ptr->size < HEAP_SIZE_LEVEL1)
	{
		ptr = nresize(ptr, 75);
	}
	else if(ptr->size < HEAP_SIZE_LEVEL2)
	{
		ptr = nresize(ptr, 50);
	}
	else if(ptr->size < HEAP_SIZE_LEVEL3)
	{
		ptr = nresize(ptr, 25);
	}
	else if(ptr->size < HEAP_SIZE_LEVEL4)
	{
		ptr = nresize(ptr, 10);
	}
	else // bigger than level 4
	{
		ptr = nresize(ptr, 2);
	}
	return ptr;
}

void exch(heap_t *heap, int a, int b)
{
	int temp = heap->values[b];
	heap->values[b] = heap->values[a];
	heap->values[a] = temp;
}

void heapinsert(heap_t * heap, int value)
{

	if(heap->size <= heap->n)
	{
		heap = heapresize(heap);
	}

	heap->values[heap->n] = value;

	int pindex = getparenti(heap, heap->n);
	int curindex = heap->n;
	while(value < heap->values[pindex])
	{
#ifdef DEBUG
	printf("DEBUG: exch(%d, %d)\n", curindex, pindex);
#endif
		exch(heap, curindex, pindex);
		curindex = pindex;
		pindex = getparenti(heap, curindex);
	}

	heap->n++;
}

int heaphead(heap_t *heap)
{
	return heap->values[0];
}

int getchildi(heap_t * heap, int index)
{
	if(heap->values[getchildi_r(heap,index)] < heap->values[getchildi_l(heap, index)])
	{
		return getchildi_r(heap, index);
	} else return getchildi_l(heap, index);
}

int heaphead_pop(heap_t *heap)
{
	if(heap->n <= 0) return 0;

	int head = heap->values[0];

	exch(heap, 0, heap->n-1);
	heap->n--;

	int curindex = 0;
	int childindex = getchildi(heap, curindex);

	while(heap->values[curindex] > heap->values[childindex])
	{
		exch(heap, curindex, childindex);
		curindex = childindex;
		childindex = getchildi(heap, childindex);
	}

	return head;
}

#ifdef HEAP_SIZE_DEFAULT
heap_t * heapnew()
{
	return heap_init();
}
#endif

#ifndef HEAP_SIZE_DEFAULT
heap_t *heapnew(size_t size)
{
	return nheap_init(size);
}
#endif

void printheap(heap_t *heap)
{
	printf("heap:\t");
	for(int i = 0; i < heap->n; i++)
	{
		printf("%d ", heap->values[i]);
	}
	printf("\n");
	printf("indx:\t");
	for(int i = 1; i < heap->n+1; i++)
	{
		printf("%*d ", heap->values[i-1]/10+1,i);
	}
	printf("\n");
}

void printordered(heap_t *heap)
{
	printf("Popping all values of heap: ");
	while(heap->n > 0)
	{
		printf("%d ", heaphead_pop(heap));
	}
	printf("\n");
}

int main()
{
	heap_t * heap = heapnew();
	heapinsert(heap, 1);
	heapinsert(heap, 4);
	heapinsert(heap, 6);
	heapinsert(heap, 9);
	heapinsert(heap, 10);
	heapinsert(heap, 5);
	heapinsert(heap, 0);
	printheap(heap);

	printordered(heap);
	heapfree(heap);
}
