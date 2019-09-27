#include "ds_array.h"
#include "ds_memory.h"


int ds_create_array() {
	long address;
	long zero = 0;
	long isSuccessful;
	long i;

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
	
	
	/* fill the array with zer0es MIGHT NOT BE ALLOWED TO */
	for(i = 0; i < MAX_ELEMENTS; i++) {
		ds_write(getFileLocationArray(i), &i, sizeof(int));
		
	}

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

	if(isIndexValid(index)) {
		return isIndexValid(index);
	}

int tester;
ds_read(&tester, getFileLocationArray(index), sizeof(int));
printf("old value %d\n", tester);

	isSuccessful = ds_write(getFileLocationArray(index), &value, sizeof(int));

ds_read(&tester, getFileLocationArray(index), sizeof(int));
printf("new value %d\n", tester);

	if(isSuccessful == -1) {
		return 2;
	}

	return 0;
}


int ds_insert(int value, long index) {
	int i;
	int old = value;
	int new;

	/* make sure the index is valid */
	if(isIndexValid(index)) {
		return isIndexValid(index);
	}
	
	if(index > elements) {
		return 1;
	}

	/* if the index is added to the end of the list */
	if(index = elements) {
		elements++;
		ds_write(getFileLocationArray(index), &value, sizeof(int));
		return 0;
	}

	if(elements == MAX_ELEMENTS) {
		return 2;
	}

	for(i = index; i < elements; i++) {

		new = old; /* put old in new */

		/*put currenet in old */
		ds_read(&old, getFileLocationArray(index), sizeof(int));

		/*put new in current */
		ds_write(getFileLocationArray(index), &new, sizeof(int));
	}

	 /* write the last element */
	ds_write(getFileLocationArray(index), &old, sizeof(int));

	elements++;

	return 0;
}

/*
int ds_delete(long index);

int ds_swap(long index1, long index2);

long ds_find(int target);

int ds_read_elements(char *filename);
*/

int ds_finish_array() {
	int isSuccessful;

printf("ds_finish array b4 ds_write \n");

	/* write the number of elements to the start of the file */
	isSuccessful = ds_write(0, &elements, sizeof(long));


	if(isSuccessful == -1) {
		return 1;
	}

printf("ds_finish array b4 ds_finish \n");


	isSuccessful = ds_finish();

	if(!isSuccessful) {
		return 2;
	}

	return 0;
}


/* helper functions */
long getFileLocationArray(long index){

	/* make sure the index is valid */
	if(isIndexValid(index)) {
		return isIndexValid(index);
	}

	printf("the size of bytes is: %ld\nthe element number is %ld of %ld\n\n",  (index * sizeof(int)) + sizeof(elements), index, elements);

	return (index * sizeof(int)) + sizeof(elements);
}

int isIndexValid(long index) {
	if (index < 0) {
		printf("less than MAX_ELEMENTS\n");
		return -2;
	}

	if (index > MAX_ELEMENTS) {
		printf("greater than MAX_ELEMENTS\n");
		return -3;
	}

	return 0; /* if successful*/
}