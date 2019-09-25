#include <stdio.h>

#define MAX_ELEMENTS 256

long elements; /* holds the current number of elements in the array */

int ds_create_array();

int ds_init_array();

int ds_replace(int value, long index);

int ds_insert(int value, long index);

int ds_delete(long index);

int ds_swap(long index1, long index2);

long ds_find(int target);

int ds_read_enements(char *filename);

int ds_finish_array();
