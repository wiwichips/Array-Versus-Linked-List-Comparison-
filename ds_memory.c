#include "ds_memory.h"

struct ds_file_struct ds_file;
struct ds_counts_struct ds_counts;

int ds_create(char *filename, long size) {
	FILE *filePointer;
	int i;
	char byte = 0; /* used so I can write 0 */
	
	/* open the file */
	filePointer = fopen(filename, "ab"); /* should this be wb+? */

	/* if filePointer is NULL return 1 */
	if (filePointer == 0) {
		return 1;
	}
	
	/* set the information for each block to 0 */
	for (i = 0; i < MAX_BLOCKS; i++) {
		ds_file.block[i].start = 0;
		ds_file.block[i].length = 0;
		ds_file.block[i].alloced = 0;
	}
	
	/* make the length of the first block size */
	ds_file.block[0].length = size;
	
	/* write the array to file */
	fwrite(ds_file.block, sizeof(&ds_file.block), 1, filePointer);
	
	/* write the bytes to the file */
	for(i = 0; i < size; i++) {
		fwrite(&byte, sizeof(char), 1, filePointer);
	}
	
	fclose(filePointer);
	return 0;
}

int ds_init(char *filename) {
	FILE *filePointer;
	
	/* try to open the file */
	filePointer = fopen(filename, "rb+");
	
	/* return 1 if the file does not exist */
	if(filePointer == 0) {
		return 1;
	}
	
	ds_file.fp = filePointer;
	
	/* read the header into the array of blocks */
	fread(ds_file.block, sizeof(ds_file.block), 1, filePointer);
	
	/* set the reads and writes to 0 */
	ds_counts.reads = 0;
	ds_counts.writes = 0;
	
	return 0;
}

long ds_malloc(long amount) {
	int i;
	int j;
	int excess;
	
	/* search through every block until find one with length >= amount */
	for(i = 0; i < MAX_BLOCKS; i++) {
		
		if(ds_file.block[i].alloced != 1 && ds_file.block[i].length >= amount){		
		
			/* look for a block to transfer the remaining bytes to */
			for(j = 0; j < MAX_BLOCKS; j++) {
				if(!ds_file.block[j].length && !ds_file.block[j].alloced && j != i) {
					
					/* find the excess amount of bytes */
					excess = ds_file.block[i].length - amount;
					
					/* set the length of the malloc'd block to amount */
					ds_file.block[i].length = amount;
					ds_file.block[i].alloced = 1;
					
					/* set the transfer block's length to the excess length */
					ds_file.block[j].length = ds_file.block[j].length + excess;
					
					/* set the new start of the block found to move stuff */
					ds_file.block[j].start = amount + ds_file.block[i].start;

					return ds_file.block[i].start;
				}
			}	
		}
	}
	printf("failure in malloc\n");
	return -1;
}

void ds_free(long start) {
	int i;
	
	/* look for the block to be freed and free it */
	for(i = 0; i < MAX_BLOCKS; i++){
		if(start == ds_file.block[i].start) {
			ds_file.block[i].alloced = 0;
			return;
		}
		
	}
	
	/* print error message */
	printf("That block doesn't exist\n");
}

void *ds_read(void *ptr, long start, long bytes) {
	long isSuccessful;
	
	/* set the position in the file. Return NULL if unsuccessful */
	isSuccessful = setPositionInFile(start);
	if(isSuccessful) {
		return NULL;
	}
	
	/* read the data into ptr. Return NULL if unsuccessful */
	isSuccessful = fread(ptr, bytes, 1, ds_file.fp);
	if(!isSuccessful) {
		return NULL;
	}
	
	/* increment the reads by 1 */
	ds_counts.reads++;
	
	return ptr;
}

long ds_write(long start, void *ptr, long bytes) {
	long isSuccessful;
	isSuccessful = setPositionInFile(start);
	if(isSuccessful) {
		return -1;
	}
	
	/* write the data into the file */
	isSuccessful = fwrite(ptr, bytes, 1, ds_file.fp);
	
	/* increment the writes by 1 */
	ds_counts.writes++;
	
	return start;
}

int ds_finish() {
	int isSuccessful = 1;
	
	isSuccessful = fseek(ds_file.fp, 0, SEEK_SET);
	
	if(isSuccessful){
		return 0;
	}
	
	fwrite(ds_file.block, sizeof(ds_file.block), 1, ds_file.fp);
	
	isSuccessful = fclose(ds_file.fp);
	
	if(isSuccessful){
		return 0;
	}
	
	/* print the number of reads and writes */
	printf("reads: %d\nwrites: %d\n", ds_counts.reads, ds_counts.writes);
	
	return 1;
}
	
/* Helper Functions */

int setPositionInFile(long start){
	int isSuccessful = 0; 
	
	/* find the size of the header */
	long headerLength = sizeof(ds_file.block) * MAX_BLOCKS;
	
	/* set the file position to the start + the headerSize */
	isSuccessful = fseek(ds_file.fp, headerLength + start , SEEK_SET);
	
	return isSuccessful;
}

/* testing functions */
void printer(){
	int i;
	int total = 15;
	
	printf("Block\t#\tstart\tlength\talloced\n");
	
	for(i = 0; i < total; i++) {
		
		printf("\t%d\t%ld\t%ld\t%d", i, ds_file.block[i].start,
		ds_file.block[i].length, ds_file.block[i].alloced);
		
		printf("\n");
		
	}
	
	
}