#include "main.h"
#include "darr/darr.h"
#include <stdio.h>

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

}

int main(int argc, char *argv[])
{
  testdarr();
}


