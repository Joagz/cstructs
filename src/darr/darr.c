#include "darr.h"
#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>

struct darr* darr_new(uint32_t capacity)
{
  struct darr *arr = (struct darr*) malloc(sizeof(struct darr));
  arr->capacity = capacity;
  arr->initial_capacity = capacity;
  arr->length = 0;

#ifndef SYS_TYPE
  exit(0);
#endif /* ifndef SYS_TYPE */

#ifdef SYS_TYPE
  switch (SYS_TYPE) {
    case SYS_64BIT:
      arr->items = calloc(capacity, SYS_64BIT_PTR_SIZE);

#ifdef DEBUG 
    printf("DEBUG: allocated items array correctly with size of %d bytes (64-bit arch)\n", SYS_64BIT_PTR_SIZE);
#endif /* ifdef  */
    break;
    case SYS_16BIT:
      arr->items = calloc(capacity, SYS_16BIT_PTR_SIZE);
#ifdef DEBUG 
    printf("DEBUG: allocated items array correctly with size of %d bytes (16-bit arch)\n", SYS_16BIT_PTR_SIZE);
#endif /* ifdef  */
    break;
    // default to 32 bit system 
    default:
      arr->items = calloc(capacity, SYS_32BIT_PTR_SIZE);
#ifdef DEBUG 
    printf("DEBUG: allocated items array correctly with size of %d bytes (32-bit arch)\n", SYS_32BIT_PTR_SIZE);
#endif /* ifdef  */
    break;
  }
#endif

  return arr;
}

// free a dynamic array
void darr_free(struct darr *ptr)
{
  for(int i = 0; i < ptr->length; i++)
    free(ptr->items[i]);

  free(ptr); 
}

void resize_arr(struct darr *ptr)
{
  ptr->items = realloc(ptr->items, (ptr->capacity + ptr->initial_capacity)*sizeof(void*));
  ptr->capacity = ptr->initial_capacity + ptr->capacity;
}

void nresize_arr(struct darr *ptr, uint32_t capacity)
{
  for(int i = capacity; i < ptr->capacity; i++){
    free(ptr->items[i]);
  }

  printf("Resizing to %d\n", capacity);
  ptr->items = realloc(ptr->items, (capacity)*sizeof(void*));
  ptr->capacity = capacity;
}


int darr_add(struct darr *arr, void*ptr)
{
  if(arr->capacity <= arr->length)
  {
    resize_arr(arr);
  }

  arr->items[arr->length] = ptr;
  arr->length++;
  return arr->length-1;
}

void *darr_get(struct darr* arr, int index)
{
  return arr->items[index];
}

// returns 0 if deleted correctly, -1 if not, and 1 if the array was resized
int darr_delete(struct darr* arr, int index)
{

  if(arr->length == 0) return -1;

  if(darr_get(arr, index) == NULL)
  {
    return -1;
  }

  arr->items[index] = NULL;

  for(int i = index; i < arr->length-1; i++)
  {
    arr->items[i] = arr->items[i+1];
  }

  // Shrink the array if the capacity is 2 the initial capacity above length
  if((arr->length+2*arr->initial_capacity) < arr->capacity)
  {
    nresize_arr(arr, arr->capacity-arr->initial_capacity);
    return 1;
  }

  arr->length--;
  return 0;
}










