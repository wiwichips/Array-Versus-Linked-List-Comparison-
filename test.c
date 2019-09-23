#include "ds_memory.h"

int main(){
	
	int dude = ds_create("test.bin", 1234);
	
	if(dude){
		printf("failure: %d\n", dude);
	}
	
	ds_init("test.bin");
		
	return 0;
}