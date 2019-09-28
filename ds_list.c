#include "ds_list.h"
#include "ds_memory.h"

/*
 *	returns 0 if successful;
 */
void ds_create_list() {
	long items = -1; /* change this variable name to pointer */
	long address;
	
	/* opens the file for reading/writing reads block array */
	ds_init("list.bin");
	
	/* ds_malloc space for a long */
	address = ds_malloc(sizeof(long));
	
	printf("the adress of the malloced' block is: %ld\n", address);
	
	if(address == -1) {
		return;
	}
	
	/* write a long value of -1*/
	ds_write(address, &items, sizeof(long));
	
	long dong;
	ds_read(&dong, 0, sizeof(long));
	
	printf("in ds creta aray, the thing is %ld\n", dong);
	
	/* call ds_finish */
	ds_finish();
}

/* call ds_init wit the list.bin file*/
int ds_init_list() {
	
	ds_init("list.bin");
	
	return 0;
}

/*
int ds_replace(int value, long index);
*/

int ds_insert(int value, long index) {
	long tempPointer;
	
	/* check the first element to see what it points to */
	ds_read(&tempPointer, 0, sizeof(long));
	
	printf("the long is %ld\n", tempPointer);
	
	/* create the sturct element to be inserted */
	struct ds_list_item_sturct ds_list_item;
	
	return 0;
}



/*
int ds_delete(long index);

int ds_swap(long index1, long index2);

long ds_find(int target);

int ds_read_elements(char *filename);

int ds_finish_list();
*/