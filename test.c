#include "ds_memory.h"

int main(){
	
	int dude = ds_create("test.bin", 0);
	
	if(dude){
		printf("failure: %d\n", dude);
	}
	
	printer(); 
	
	return 0;
}