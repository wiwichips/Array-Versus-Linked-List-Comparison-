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
		
	if(address == -1) {
		return;
	}
	
	/* write a long value of -1*/
	ds_write(address, &items, sizeof(long));
	
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
	
	struct ds_list_item_struct previous;
	struct ds_list_item_struct new;
	long size = sizeof(struct ds_list_item_struct);
	long previous_loc;
	long starter = -2;
	long head = -1;
	int i;
	
	previous_loc = 0;
	
	
	/* set the node to be inserted item to value */
	new.item = value;
	
	/* read in the first long */
	ds_read(&previous.next, 0, sizeof(long));
	
	for(i = index; i > 0; i--) {
		/* if this is reached before, there is an error */
		if(previous.next == -1) {
			return 1;
		}
		
		previous_loc = previous.next;
		
		ds_read(&previous, previous.next, size);
	}
	
	/* read the head pointer into head */
	ds_read(&head, 0, sizeof(long));
	
	if(i == 0 && previous_loc > 0) {
		
		new.next = previous.next;
		
		previous.next = ds_malloc(size);
		
		/* overwrite the old node */
		ds_write(previous_loc, &previous, size);
		
		/* write thew new node */
		ds_write(previous.next, &new, size);
		
		
	} else if (head > 0){
		/* set the next equal to head */
		new.next = head;
		
		/* allocate space for the new node */
		previous.next = ds_malloc(size);
		
		/* make the head pointer point to the new location */
		head = previous.next;
		ds_write(0, &head, sizeof(long));
		
		/* write the new node to the file */
		ds_write(head, &new, size);
		
	} else { printf("else\n");
		new.next = -1;
		
		starter = ds_malloc(size);
		
		/* write the pointer to the first node */
		ds_write(0, &starter, sizeof(long));
		
		/* write the new node to be inserted */
		ds_write(starter, &new, size);
		
	}
	
	return 0;
}

/*
int ds_delete(long index);

int ds_swap(long index1, long index2);

long ds_find(int target);

int ds_read_elements(char *filename);

int ds_finish_list();
*/

/* test functions DELETE THESE LATER 
long ds_write(long start, void *ptr, long bytes)
void *ds_read(void *ptr, long start, long bytes)
*/
/*
int ds_delete(long index);

int ds_swap(long index1, long index2);

long ds_find(int target);

int ds_read_elements(char *filename);
*/

int ds_finish_list() {
	int isSuccessful;
	
	isSuccessful = ds_finish();

	if(!isSuccessful) {
		return 1;
	}
	
	return 0;
	
}

/* ~~~~~~~~ HELPER FUNCTIONS ~~~~~~~~ */

/* returns the address when given an index. Return neg val on fail */
long addressor(long index) {
	int i;
	long pointer;
	long size = sizeof(struct ds_list_item_struct);
	struct ds_list_item_struct new;
	
	/* read the first pointer to the first node */
	ds_read(&pointer, 0, sizeof(long));
	
	for(i = index; i > 0; i--) {
		
		ds_read(&new, pointer, size);
		pointer = new.next;
		
	}
	
	return new.next;
	
}


/* test functions DELETE THESE LATER 
long ds_write(long start, void *ptr, long bytes)
void *ds_read(void *ptr, long start, long bytes)
*/
void createFakeListInFile() {
	long head = sizeof(long);
	struct ds_list_item_struct plug1;
	struct ds_list_item_struct plug2;
	struct ds_list_item_struct plug3;
	struct ds_list_item_struct plug4;
	long size = sizeof(struct ds_list_item_struct);
	struct ds_list_item_struct temp;
	
	/* made the head poiner point to 8 */
	ds_write(0, &head, sizeof(long));
	
	ds_malloc(size);
	
	/* create three nodes */
	plug1.item = 101;
	plug1.next = ds_malloc(size);
	
	plug2.item = 102;
	plug2.next = ds_malloc(size);
	
	plug3.item = 103;
	plug3.next = ds_malloc(size);
	
	plug4.item = 104;
	plug4.next = -1;
	
	/* write them to file */
	ds_write(head, &plug1, size);
	ds_write(plug1.next, &plug2, size);
	ds_write(plug2.next, &plug3, size);
	ds_write(plug3.next, &plug4, size);
	
	/* read them to output to test they work */
	ds_read(&temp, head, size);
	printf(")\tthe item is %d\n\tthe next is %ld\n\n", temp.item, temp.next);
	
	ds_read(&temp, plug1.next, size);
	printf(")\tthe item is %d\n\tthe next is %ld\n\n", temp.item, temp.next);
	
	ds_read(&temp, plug2.next, size);
	printf(")\tthe item is %d\n\tthe next is %ld\n\n", temp.item, temp.next);
	
	ds_read(&temp, plug3.next, size);
	printf(")\tthe item is %d\n\tthe next is %ld\n\n", temp.item, temp.next);
	
	return;
}

void listPrint(){ printf("~~~~~~~~~~~ listPrint ~~~~~~~~~~~\n");
	int i;
	long dog;
	struct ds_list_item_struct cat;
	long catSize = sizeof(struct ds_list_item_struct);
	
	ds_read(&dog, 0, sizeof(long));
	
	for(i=0;dog != -1;i++) {
		ds_read(&cat, dog, catSize);
		dog = cat.next;
		
		printf("Linked[%d] = %d\t\tNext = %ld\n", i, cat.item, cat.next);
		
		if(i > 15) { break;}
	}
	
	
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"); return;
}
