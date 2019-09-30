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

/* do error checking */
int ds_replace(int value, long index) {
	long address;
	struct ds_list_item_struct temp;
	long size = sizeof(struct ds_list_item_struct);
	
	/* get the address of the index */
	address = addressor(index);
	
	/* read in the struct at thet address */
	ds_read(&temp, address, size);
	
	/* change the item to the value */
	temp.item = value;
	
	/* write the struct to the file */
	ds_write(address, &temp, size);
	
	return 0;
}

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
		
	} else {
		new.next = -1;
		
		starter = ds_malloc(size);
		
		/* write the pointer to the first node */
		ds_write(0, &starter, sizeof(long));
		
		/* write the new node to be inserted */
		ds_write(starter, &new, size);
	}


	return 0;
}

int ds_delete(long index) {
	long address;
	struct ds_list_item_struct tempPre;
	struct ds_list_item_struct temp;
	long size = sizeof(struct ds_list_item_struct);
	
	if(index < 0) {
		return 1;
	}
	
	/* get the address of the index and read it*/
	address = addressor(index);
	
	if(address < 0) {
		return 2;
	}
	
	ds_read(&temp, address, size);
	
	/* ds_free the memory for the specified index */
	ds_free(address);	
	
	if(index == 0) {
		ds_write(0, &temp.next, sizeof(long));
		return 0;
	}
	
	/* get the address of the index before and read it*/
	address = addressor(index - 1);
	ds_read(&tempPre, address, size);
	
	/* set the next for the previous block */
	tempPre.next = temp.next;
	
	/* overwrite the node before the index with updated next */
	ds_write(address, &tempPre, size);
	
	return 0;
}

int ds_swap(long index1, long index2) {
	long address1;
	long address2;
	long tempAddress;
	struct ds_list_item_struct temp1;
	struct ds_list_item_struct temp2;
	long size = sizeof(struct ds_list_item_struct);
	
	if(index1 < 0 || index2 < 0) {
		return 1;
	}
	
	/* get the addresses of the indecies */
	address1 = addressor(index1);
	address2 = addressor(index2);
	
	if(address1 < 0 || address2 <0) {
		return 2;
	}
	
	/* read in the nodes */
	ds_read(&temp1, address1, size);
	ds_read(&temp2, address2, size);
	
	/* swap the pointers */
	tempAddress = temp1.next;
	temp1.next = temp2.next;
	temp2.next = tempAddress;
	
	/* write them in their swapped locations */
	ds_write(address2, &temp1, size);
	ds_write(address1, &temp2, size);
	
	return 0;
}

long ds_find(int target) {
	int i;
	long pointer;
	long size = sizeof(struct ds_list_item_struct);
	struct ds_list_item_struct new;

	/* read in the first long */
	ds_read(&new.next, 0, sizeof(long));
	
	for(i = 0; new.item == target || new.next != -1; i++) {
		/* if this is reached before, there is an error */
		if(new.next == -1) {
			return 1;
		}
		
		/* save the old poijnter */
		pointer = new.next;
		
		/* read in the new struct */
		ds_read(&new, new.next, size);
				
		if(new.item == target) {
			return pointer;
		}
	}

	
	return -10;
}

/* have not error chekced this yet */
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
	
	if(index < 0) {
		return -1;
	}
	
	/* read the first pointer to the first node */
	ds_read(&pointer, 0, sizeof(long));
	
	if(index == 0 && pointer >0) {
		return pointer;
	}
	
	if(pointer == -1) {
		return -2;
	}
	
	for(i = index; i > 0; i--) {
		ds_read(&new, pointer, size);
		pointer = new.next;
		
		if(new.next==-1){
			return -3;
		}
	}
	
	return new.next;
}


/* test functions DELETE THESE LATER 
long ds_write(long start, void *ptr, long bytes)
void *ds_read(void *ptr, long start, long bytes)
*/

void listPrint(){
	int i;
	long dog;
	struct ds_list_item_struct cat;
	long catSize = sizeof(struct ds_list_item_struct);
	
	printf("~~~~~~~~~~~ listPrint ~~~~~~~~~~~\n");
	
	ds_read(&dog, 0, sizeof(long));
	
	for(i=0;dog != -1;i++) {
		ds_read(&cat, dog, catSize);
		dog = cat.next;
		
		printf("Linked[%d] = %d\t\tNext = %ld\n", i, cat.item, cat.next);
		
		if(i > 15) { break;}
	}
	
	
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"); return;
}
