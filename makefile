
l: ds_memory.o test.o ds_memory.h
	gcc test.o ds_memory.o ds_memory.h -o l
	
test.o: test.c 
	gcc test.c -Wall -ansi -pedantic -o test.o -c

ds_memory.o: ds_memory.c
	gcc ds_memory.c -Wall -ansi -pedantic -o ds_memory.o -c

clean:
	rm *.o
	rm *.bin