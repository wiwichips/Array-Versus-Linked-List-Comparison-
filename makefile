
a1: ds_memory.o test.o ds_memory.h
	gcc test.o ds_memory.o ds_memory.h -o a1
	
test.o: test.c 
	gcc test.c -o test.o -c

ds_memory.o: ds_memory.c
	gcc ds_memory.c -o ds_memory.o -c