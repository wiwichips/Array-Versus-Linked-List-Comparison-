#include "ds_memory.h"

struct ds_file_struct ds_file;
struct ds_counts_struct ds_counts;

/* just use this to test my makefile etc */
void printer(){
	printf("ewrwerewrwe\n");
	
	
	return;
}

int ds_create(char *filename, long size) {
	FILE *filePointer;
	int i;
	
	/* open the file */
	filePointer = fopen(filename, "a");

	/* if filePointer is NULL return 1 */
	if (filePointer == 0) {
		return 1;
	}

	/* set the initial block information */
	ds_file.fp = filePointer;
	
	
	/* set the information for each block to 0 */
	for (i = 0; i < MAX_BLOCKS; i++) {
		ds_file.block[i].start = 0;
		ds_file.block[i].length = 0;
		ds_file.block[i].alloced = 0;
	}
	
	/* set the first block length to size */
	ds_file.block[0].length = size;
	
	/* write the array to file */
	fwrite(ds_file.block, sizeof(ds_file.block), 1, filePointer);
	
	fclose(filePointer);
	return 0;
}

/*
int ds_init(char *filename);

long ds_malloc(long amount);

void ds_free(long start);

void *ds_read(void *ptr, long start, long bytes);

long ds_write(long start, void *ptr, long bytes);

int ds_finish();
*/