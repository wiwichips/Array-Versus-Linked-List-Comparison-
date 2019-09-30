#include "ds_memory.h"
#include "ds_array.h"
#include <stdlib.h> 

void thing();
void readtester();
void testarray();
void show_array();
void insert(int v0, int v1, long v2);
void myArrayFunction();
void clearOutput();
void calldsinit();
void creamList();
void makeARandomFile(int howMany);
void hahahaha();
int runExperimentsW(int howMany);
int runExperimentsR(int howMany);
int dude(int howMany);
int arraydude(int howMany);
void runner();

int main() { clearOutput(); 
	
	runner();
	
	return 0;
}

void runner() {
	int i;
	int j;
	FILE *fp;
	
	fp = fopen("writes.csv", "w");
	
	/* first lets worry about the reads */
	for( j = 0; j <30; j++) {
		
		
		for(i = 10; i <=100; i = i +10) {
			fprintf(fp, "%d,", arraydude(i));
			
			
			
		}
		
		fprintf(fp, "\n");


	}
	
	
	fclose(fp);
	
	
}

int arraydude(int howMany){
	int i;
	int numThings;
	
	
	
	ds_create("array.bin", 8000); /* create the file */
	ds_create_array();	
	ds_init_array();

	
	makeARandomFile(howMany);
	ds_read_elements("test.txt");
	
	for(i = 0; i < howMany; i++) {
		ds_delete(rand()%howMany);
		
	}
	
	numThings = ds_counts.reads;
	
	ds_finish_array();
	
	return numThings;

}
/*
int dude(int howMany){
	int i;
	int numThings;
	
	
	
	ds_create("list.bin", 2048); 

	ds_create_list();
	ds_init_list();
	
	makeARandomFile(howMany);
	ds_read_elements("test.txt");
	
	for(i = 0; i < howMany; i++) {
		ds_swap(rand()%howMany, rand()%howMany);
		
	}
	
	numThings = ds_counts.reads;
	
	ds_finish_list();
	
	return numThings;

}
*/
/* create a file - makes a file with 100 random ints */
void makeARandomFile(int howMany) {
	int i;
	FILE *fp;
	int num;
	fp = fopen("test.txt", "w");
	
	for(i =0; i < howMany; i++) {
		num = rand();
		fprintf(fp, "%d\n", num);
		
	}
	
	fclose(fp);
	
	
}

/*

void hahahaha(){
	
	
	int i;
	FILE *fp;
	int num;
	fp = fopen("writes.csv", "w");
	
	
		fprintf(fp, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",
	runExperimentsW(10),
	runExperimentsW(20),
	runExperimentsW(30),
	runExperimentsW(40),
	runExperimentsW(50),
	runExperimentsW(60),
	runExperimentsW(70),
	runExperimentsW(80),
	runExperimentsW(90),
	runExperimentsW(100));

	
	fclose(fp);
	
	
	
	

	
}

int runExperimentsW(int howMany) {
	int i;
	int num;
	
	ds_create("list.bin", 2048); 

	ds_create_list();
	ds_init_list();
	
	makeARandomFile(howMany);
	
	for(i = 0; i < 1; i++) {
		ds_create("list.bin", 2048); 

	ds_create_list();
	ds_init_list();
		
		num = rand()%howMany;
		printf("\n\nRUNEXPERIMENTSW\n%d\n", num);
		
		ds_read_elements("test.txt");
		
		ds_replace(rand(),num);
		
			
	

	ds_finish_list();
	}
	

	
	return ds_counts.writes;
}




void calldsinit(){

	ds_create("list.bin", 2048);

	ds_create_list();
	ds_init_list();
	
	
	ds_insert(101,0);
	ds_insert(102,1);
	ds_insert(103,2);
	
	ds_insert(204,0);
	
	ds_insert(305,-1);
	ds_insert(306,-23);
	ds_insert(307,0);
	ds_insert(309,7);
	ds_delete(1);
	ds_delete(1);
	ds_delete(1);
	ds_insert(410,2);
	ds_insert(411,2);
	ds_insert(412,3);
	
	listPrint();
	
	printf("ds_find(410) = %ld\n", ds_find(410));
	
	listPrint();
	
	printf("find ds_find(%d) = %ld\n", 309, ds_find(309));

	printer();
	
	ds_finish_list();

}

void creamList(){
	
	ds_create("list.bin", 2048);

	ds_create_list();
	

	ds_init_list();
	ds_insert( 0, 0 );
	ds_insert( 1, 1 );
	ds_insert( 1, 2 );
	ds_insert( -1, 0 );
	ds_insert( -2, 0 );
	ds_insert( -3, 0 );

	

	listPrint();

	ds_finish_list();
	
	
	return;
}*/

/* for ds_array */

void myArrayFunction(){
	ds_create("array.bin", 2048);
	ds_create_array();	
	ds_init_array();
	
	
	printf("\n\ncalling ds_insert \n\n\n");
	
	makeARandomFile(10);
	ds_read_elements("test.txt");
 printf("show array\n");
	show_array();
	
	 printf("show array\n");
	show_array();
	
	
	
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
	
	long memory[12]; 
	
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
	

	ds_create( "test.bin", 1234);
	
	
	ds_init("test.bin");
	
	
	memory[0] = ds_malloc(sizeof(c1));
	ds_write(memory[0], &c1, sizeof(c1));
	
	memory[1] = ds_malloc(sizeof(c2));
	ds_write(memory[1], &c2, sizeof(c2));
	
	ds_free(memory[1]);
	
	
	memory[2] = ds_malloc( sizeof(s1));
	ds_write(memory[2], &s1, sizeof(s1));
	
	memory[3] = ds_malloc(sizeof(s1));
	ds_write(memory[3], &s2, sizeof(s2));
	
	ds_free(memory[3]);
	
	
	memory[4] = ds_malloc(sizeof(i1));
	ds_write(memory[4], &i2, sizeof(i2));
	
	printf("////// - BEFORE 5 - ////////\n\n");
	
	memory[5] = ds_malloc(sizeof(i1));
	ds_write(memory[5], &i1, sizeof(i1));
	
	ds_free(memory[5]);
	
	printf("////// - BEFORE 6 - ////////\n\n");


	memory[6] = ds_malloc(sizeof(l1));
	ds_write(memory[6], &l1, sizeof(l1));
	
	printf("////// - BEFORE 7 - ////////\n\n");

	memory[7] = ds_malloc(sizeof(l2));
	ds_write(memory[7], &l2, sizeof(l2));
	
	ds_free(memory[7]);
	
	printf("////// - BEFORE 8 - ////////\n\n");


	memory[8] = ds_malloc(sizeof(f1));
	ds_write(memory[8], &f1, sizeof(f1));
	
	printf("////// - BEFORE 9 - ////////\n\n");

	memory[9] = ds_malloc(sizeof(f2));
	ds_write(memory[9], &f2, sizeof(f2));
	
	printf("////// - BEFORE free(9) - ////////\n\n");
	
	ds_free(memory[9]);
	
	printf("////// - BEFORE 10 - ////////\n\n");


	memory[10] = ds_malloc(sizeof(d1));
	ds_write(memory[10], &d1, sizeof(d1));
	
	printf("////// - BEFORE 11 - ////////\n\n");

	memory[11] = ds_malloc(sizeof(d2));
	ds_write(memory[11], &d2, sizeof(d2));
	
	ds_free(memory[11]);
	
	
	
	printf("Remaining memory allocations:\n");
	for(i = 0; i < 12; i+=2) {
		printf("%ld\n", memory[i]);
		
	}
	

	
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


void clearOutput(){
	int i;
	for(i = 0; i < 20; i++){
		printf("\n");
	}
	return;
}
