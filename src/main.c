#include "main.h"
#include "darr/darr.h"
#include "linkedlist/linkedlist.h"
#include <stdio.h>
#include <stdlib.h>

void testdarr()
{
  struct darr *arr = darr_new(2);
  int item_1 = 1;
  int item_2 = 2;
  int item_3 = 3;
  int item_4 = 4;

  void* ptr_1 = (void*) &item_1;
  void* ptr_2 = (void*) &item_2;
  void* ptr_3 = (void*) &item_3;
  void* ptr_4 = (void*) &item_4;

  darr_add(arr, ptr_1);
  darr_add(arr, ptr_2);
  darr_add(arr, ptr_3);
  darr_add(arr, ptr_4);
 
  printf("ARR CAPACITY: %d\n", arr->capacity);

  for(int i = 0; i < arr->length; i++ )
    printf("Arr[%d] = %d\n", i, *((int*)arr->items[i]));
  int i = 0;

  darr_delete(arr, 0);
  printf("Arr[%d] = %d\n", i, *((int*)arr->items[i]));

  darr_delete(arr, 0);
  printf("Arr[%d] = %d\n", i, *((int*)arr->items[i]));

  darr_delete(arr, 0);
  printf("Arr[%d] = %d\n", i, *((int*)arr->items[i]));

  darr_delete(arr, 0);
  darr_free(arr);
}

int main(int argc, char *argv[])
{

  struct linkedlist *l = linkedlist_new();
 
  printf("linkedlist created successfully\n");
  int num = 0;
  int num1 = 1;
  int num2 = 2;

  linkedlist_prepend(l,(void*) &num);
  linkedlist_prepend(l,(void*) &num1);
  linkedlist_append(l,(void*) &num2);

  printf("l[0] = %d\n", *((int*)linkedlist_get(l, 0)->ptr));
  printf("l[1] = %d\n", *((int*)linkedlist_get(l, 1)->ptr));
  printf("l[2] = %d\n", *((int*)linkedlist_get(l, 2)->ptr));

  linkedlist_free(l);
}


