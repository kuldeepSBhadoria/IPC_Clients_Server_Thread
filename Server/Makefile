#!/bin/bash

server_t: server_t.o requestProcess.o
	gcc -o server_t server_t.o requestProcess.o -lpthread

server_t.o: server_t.c headers.h prototypes.h 
	gcc -c server_t.c 

requestProcess.o: requestProcess.c headers.h prototypes.h 
	gcc -c requestProcess.c 
clean:
	rm *.o
	-rm server_t

