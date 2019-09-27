#include "ds_memory.h"
#include "ds_array.h"

void thing();
void readtester();
void testarray();
void show_array();
void insert(int v0, int v1, long v2);
void myArrayFunction();
void clearOutput();

int main(){ clearOutput(); 
	myArrayFunction();
	
	
	
	
	
	
	return 0;
}

/* for ds_array */

void myArrayFunction(){
	ds_create("array.bin", 2048);
	
	ds_create_array();	
	
	ds_init_array();
	
	printf("//// Calling printer\n");
	printer();
	
	
	
	/*show_array();*/printf("show array\n");
	show_array();
	
	/* add something to it */
	printf("\n\ncalling ds_insert \n\n\n");
	ds_insert(420, 0);
	ds_insert(23, 1);
	ds_insert(32, 2);
	ds_insert(69,0);
	
	
	/*show_array();*/ printf("show array\n");
	show_array();
	
	printf("//// Calling printer\n");
	printer();
	
	printf("//// Calling ds_finish\n");
	ds_finish_array();
	
}

void insert(int v0, int v1, long v2) {
	int value;
	long index;
	value = v1;
	index = v2;
	ds_init_array();
	ds_insert( value, index );
	ds_finish_array();
}

void testarray(){
	
	/* create binary file */
	int dude = ds_create( "array.bin", 2048);
	if (dude){
		printf("Error in ds_create: %d\n", dude);
	}
	
	ds_create_array();
	
	ds_init_array();
	
	show_array();
	
	ds_finish();
}

void show_array(){
	int i;
	int q = 0;
		
	printf("number of elements in show_array: %ld\n", elements);
	
	for(i = 0; i < elements; i++) {
		ds_read(&q, i * sizeof(int) + sizeof(long), sizeof(int));
		printf("\tarray[%d] = %d\n", i, q);
		
	}
	
}

/* for ds_memory */
void thing(){
	
	
	unsigned char c1;
	unsigned char c2;
	unsigned short s1;
	unsigned short s2;
	unsigned int i1;
	unsigned int i2;
	unsigned long l1;
	unsigned long l2;
	float f1;
	float f2;
	double d1;
	double d2;
	
	long memory[12]; /* array to hold all memory allocations */
	
	int i;
	c1 = 1;
	c2 = 2;
	s1 = 3;
	s2 = 4;
	i1 = 5;
	i2 = 6;
	l1 = 7;
	l2 = 8;
	f1 = 9.0;
	f2 = 10.0;
	d1 = 11.0;
	d2 = 12.0;
	
	/* create binary file */
	ds_create( "test.bin", 1234);
	
	/* load block array and reset counts */
	ds_init("test.bin");
	
	/* allocate and weite chars, free one of them */
	memory[0] = ds_malloc(sizeof(c1));
	ds_write(memory[0], &c1, sizeof(c1));
	
	memory[1] = ds_malloc(sizeof(c2));
	ds_write(memory[1], &c2, sizeof(c2));
	
	ds_free(memory[1]);
	
	/* allocate and write shorts, free one of them */
	memory[2] = ds_malloc( sizeof(s1));
	ds_write(memory[2], &s1, sizeof(s1));
	
	memory[3] = ds_malloc(sizeof(s1));
	ds_write(memory[3], &s2, sizeof(s2));
	
	ds_free(memory[3]);
	
	/* allocate and write ints, free one of them */
	memory[4] = ds_malloc(sizeof(i1));
	ds_write(memory[4], &i2, sizeof(i2));
	
	printf("////// - BEFORE 5 - ////////\n\n");
/*	printer();*/	
	memory[5] = ds_malloc(sizeof(i1));
	ds_write(memory[5], &i1, sizeof(i1));
	
	ds_free(memory[5]);
	
	printf("////// - BEFORE 6 - ////////\n\n");
/*	printer();*/	
	/* allocate and write longs, free one of them */
	memory[6] = ds_malloc(sizeof(l1));
	ds_write(memory[6], &l1, sizeof(l1));
	
	printf("////// - BEFORE 7 - ////////\n\n");
/*	printer();*/	
	memory[7] = ds_malloc(sizeof(l2));
	ds_write(memory[7], &l2, sizeof(l2));
	
	ds_free(memory[7]);
	
	printf("////// - BEFORE 8 - ////////\n\n");
/*	printer();*/	
	/* allocate and write floats, free one of them */
	memory[8] = ds_malloc(sizeof(f1));
	ds_write(memory[8], &f1, sizeof(f1));
	
	printf("////// - BEFORE 9 - ////////\n\n");
/*	printer();*/	
	memory[9] = ds_malloc(sizeof(f2));
	ds_write(memory[9], &f2, sizeof(f2));
	
	printf("////// - BEFORE free(9) - ////////\n\n");
/*	printer();*/	
	ds_free(memory[9]);
	
	printf("////// - BEFORE 10 - ////////\n\n");
/*	printer();*/	
	/* allocate and write d oubles free one of them */
	memory[10] = ds_malloc(sizeof(d1));
	ds_write(memory[10], &d1, sizeof(d1));
	
	printf("////// - BEFORE 11 - ////////\n\n");
/*	printer();*/	
	memory[11] = ds_malloc(sizeof(d2));
	ds_write(memory[11], &d2, sizeof(d2));
	
	ds_free(memory[11]);
	
	
	/* print this out so I can understand it and test it */
	printf("Remaining memory allocations:\n");
	for(i = 0; i < 12; i+=2) {
		printf("%ld\n", memory[i]);
		
	}
	
/*	printer();*/
	
	ds_finish();
	
	return;
}

void readtester(){
	
	unsigned char c1;
	unsigned short s1;
	unsigned int i1;
	unsigned long l1;
	float f1;
	double d1;
	long memory [6] = { 0, 2, 6, 14, 30};
	
	/* values copied from output of ds_write */
	ds_init( "test.bin");

	ds_read( &c1, memory[0],sizeof( c1 ) );
	ds_read( &s1, memory[1],sizeof( s1 ) );
	ds_read( &i1, memory[2],sizeof( i1 ) );
	ds_read( &l1, memory[3], sizeof( l1 ) );
	ds_read( &f1, memory[4],sizeof( f1 ) );
	ds_read( &d1, memory[5],sizeof( d1 ) );
	
	printf( "%d%d%d%ld%f%f\n", c1, s1, i1, l1, f1, d1 );
	
	ds_finish();
	
	return;
}

/* helper functions for formatting */
void clearOutput(){
	int i;
	for(i = 0; i < 20; i++){
		printf("\n");
	}
	return;
}

