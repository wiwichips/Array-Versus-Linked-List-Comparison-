#include "ds_memory.h"

int main(){
	
	int dude = ds_create("test.bin", 1234);
	
	if(dude){
		printf("failure: %d\n", dude);
	}
	
	ds_init("test.bin");
	
	
	
	printf("\nthe location is %ld\n\n", ds_malloc(12));
	
	printf("\nthe location is %ld\n\n", ds_malloc(543));

	printf("\nthe location is %ld\n\n", ds_malloc(853));
	
	printf("\nthe location is %ld\n\n", ds_malloc(92));
	
	
	return 0;
}