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

	if(isIndexValid(index)) {
		return isIndexValid(index);
	}

	isSuccessful = ds_write(getFileLocationArray(index), &value, sizeof(int));

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
	if(index == elements) {
		elements++;
		ds_write(getFileLocationArray(index), &value, sizeof(int));
		return 0;
	}

	if(elements == MAX_ELEMENTS) {
		return 2;
	}

	for(i = index; i < elements; i++) {
		/* put old in new */
		new = old;
		
		/* read the old value into the variable 'old' */
		ds_read(&old, getFileLocationArray(i), sizeof(int));
		
		/* write the new value where the old one was */
		ds_write(getFileLocationArray(i), &new, sizeof(int));
	}
	 /* write the last element */
	ds_write(getFileLocationArray(i), &old, sizeof(int));

	elements++;
	
	return 0;
}

int ds_delete(long index) {
	int i;
	int temp = 0;
	
	if(isIndexValid(index)) {
		return isIndexValid(index);
	}
	
	if( index >= elements) {
		return 1;
	}
	
	/* write each element over the old one in the previous column */
	for(i = index; i < elements; i++) {
		
		
		ds_read(&temp, getFileLocationArray(i+1), sizeof(int));
		
		ds_write(getFileLocationArray(i), &temp, sizeof(int));
		
		
	}
	
	elements--;
	return 0;
}

int ds_swap(long index1, long index2) {
	long isSuccessful;
	int value1;
	int value2;
	
	/* error checking */
	if(index1 < 0 || index2 < 0) {
		return 10;
	}
	
	if(index1 > elements || index2 > elements) {
		return 11;
	}
	
	/* Read in the value at index1 */
	ds_read(&value1, getFileLocationArray(index1), sizeof(int));
	
	/* Read in the value at index2 */
	ds_read(&value2, getFileLocationArray(index2), sizeof(int));
	
	/* write the value of index 2 into index 1 */
	isSuccessful = ds_write(getFileLocationArray(index1), &value2, sizeof(int));
	
	if(!isSuccessful) {
		return 20;
	}
	
	
	/* write the value of index 1 into index 2 */
	ds_write(getFileLocationArray(index2), &value1, sizeof(int));
	
	if(!isSuccessful) {
		return 21;
	}
	
	return 0;
}

long ds_find(int target) {
	int i;
	int temp = 0;
	
	for(i = 0; i < elements; i++) {
		ds_read(&temp, getFileLocationArray(i), sizeof(int));
		
		if(temp == target) {
			return i;
		}
		
	}
	
	return -1;
}



int ds_read_elements(char *filename) {
	int temp;
	int i;
	FILE *filePointer;

	/* open file, */
	filePointer = fopen(filename, "r"); /* remember to ERROR CHECK*/

	i = 0;

	/* read the number of elements */
	while(fscanf(filePointer, "%d", &temp)!=EOF){
		ds_insert(temp,i);
		i++;
	}

	fclose(filePointer);
	
	return 0;
}

int ds_finish_array() {
	int isSuccessful;

	/* write the number of elements to the start of the file */
	isSuccessful = ds_write(0, &elements, sizeof(long));


	if(isSuccessful == -1) {
		return 1;
	}

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