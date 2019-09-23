#include "ds_memory.h"

struct ds_file_struct ds_file;
struct ds_counts_struct ds_counts;

int ds_create(char *filename, long size) {
	FILE *filePointer;
	int i;
	char byte = 0; /* used so I can write 0 */
	
	/* open the file */
	filePointer = fopen(filename, "a");

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
	fwrite(ds_file.block, sizeof(ds_file.block), 1, filePointer);
	
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
	filePointer = fopen(filename, "r+");
	
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
int k;
	
	/* search through every block until find one with length >= amount */
	for(i = 0; i < MAX_BLOCKS; i++) {
		if(!ds_file.block[i].alloced && ds_file.block[i].length >= amount) {		
			
			/* look for a block to transfer the remaining bytes to */
			for(j = 0; j < MAX_BLOCKS; j++) {
				if(ds_file.block[j].length == 0 && !ds_file.block[j].alloced) {
					/* set the transfer block's length to the excess length */
					ds_file.block[j].length = ds_file.block[i].length - amount;
					
					/* set the malloced' block to alloced and to the amount */
					ds_file.block[i].alloced = 1;
					ds_file.block[i].length = amount;
					
					/* set the start of the block new shifted block */
					ds_file.block[j].start = ds_file.block[j-1].length
					+ ds_file.block[j-1].start;

					
printf("Block #\t\t start\t\tlength\t\talloced\n");
for(k = 0; k < 15; k++) {
printf("%d\t\t%ld\t\t%ld\t\t%d\n", 
k, ds_file.block[k].start, ds_file.block[k].length, 
ds_file.block[k].alloced);
}
					
					return ds_file.block[i].start;
				}
			}	
		}
	}
	
	return -1;
}

void ds_free(long start) {
	int i;
	
	/* look for the block to be freed and free it */
	for(i = 0; i < MAX_BLOCKS; i++){
		if(start == ds_file.block[i].start) {
			ds_file.block[i].alloced = 0;
		}
		
	}
	
	/* print error message */
	printf("That block doesn't exist\n");
}

/*
void *ds_read(void *ptr, long start, long bytes);

long ds_write(long start, void *ptr, long bytes);

int ds_finish();
*/