
l: ds_memory.o ds_array.o test.o ds_memory.h ds_array.h
	gcc test.o ds_memory.o ds_array.c ds_memory.h ds_array.h -o l
	
test.o: test.c 
	gcc test.c -Wall -ansi -pedantic -o test.o -c

ds_memory.o: ds_memory.c
	gcc ds_memory.c -Wall -ansi -pedantic -o ds_memory.o -c

ds_array.o: ds_array.c
	gcc ds_memory.c -Wall -ansi -pedantic -o ds_array.o -c

clean:
	rm *.o
	rm *.bin