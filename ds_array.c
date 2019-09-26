#include "ds_array.h"
#include "ds_memory.h"


int ds_create_array() {
	long address;
	long zero = 0;
	long isSuccessful;

	/* open the file */
	isSuccessful = ds_init("array.bin");

	if(isSuccessful) {
		return 1;
	}
	
	/* allocate a long of memory */
	address = ds_malloc(sizeof(long));

	/* write a zero into the malloced block */
	isSuccessful = ds_write(address, &zero, sizeof(long));

	if(isSuccessful == -1) {
		return 2;
	}

	/* allocate memory for the whole array */
	isSuccessful = ds_malloc(MAX_ELEMENTS * sizeof(int));

	if(isSuccessful == -1) {
		return 3;
	}
	
	/* close the file */
	isSuccessful = ds_finish();

	if(!isSuccessful) {
		return 4;
	}
	
	return 0;
}


int ds_init_array() {
	long isSuccessful;
	long * isSuccessfulPointer;
	
	/* open the file */
	isSuccessful = ds_init("array.bin");
	
	if(isSuccessful) {
		return 1;
	}
	
	/* read the number of elements into the global variable elements */
	isSuccessfulPointer = ds_read(&elements, 0, sizeof(long));
	
	if(isSuccessfulPointer==NULL) {
		return 2;
	}
	
	printf("number of elements: %ld\n", elements);
	
	return 0;
}


int ds_replace(int value, long index) {
	long isSuccessful;

	if(index >= MAX_ELEMENTS || index < 0) {
		return 1;
	}

int tester;
ds_read(&tester, index * sizeof(int), sizeof(int));
printf("old value %d\n", tester);
	
	isSuccessful = ds_write(index * sizeof(int), &value, sizeof(int));

ds_read(&tester, index * sizeof(int), sizeof(int));
printf("new value %d\n", tester);

	if(isSuccessful == -1) {
		return 2;
	}
	
	return 0;
}

/*
int ds_insert(int value, long index);

int ds_delete(long index);

int ds_swap(long index1, long index2);

long ds_find(int target);

int ds_read_enements(char *filename);

int ds_finish_array();
*/