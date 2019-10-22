#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
//#include <time.h>
#include <limits.h>
#include <string.h>
//#include "Periodic_Data.h"
#include "FIFO_Stack.h"

#define BUFFER_SIZE 256
#define CAPACITY 20

/*typedef struct STACK STACK;

struct STACK {
	
	char* stack[CAPACITY];
	int lowestFree;
	int nb_elem;
	int array[CAPACITY]; 
	
};*/

void StackInit(STACK *p_stack) {
	//p_stack->array = {[0 ... CAPACITY-1] = INT_MAX};
	p_stack->nb_elem = 0;
	p_stack->lowestFree = INT_MAX;	
	for (int i=0; i<CAPACITY; i++) {
		p_stack->array[i] = INT_MAX;
		p_stack->stack[i] = malloc(BUFFER_SIZE*sizeof(char));		
	}
}

void StackPush(STACK *p_stack, char* buffer) {
	int counter = 0;
	int finished = 0;
	int found = 0;
	// Push position into array
	p_stack->array[p_stack->nb_elem] = p_stack->lowestFree;
	// Update number of elements
	p_stack->nb_elem++;
	// Allocate the buffer to a memory position
	memcpy(p_stack->stack[p_stack->lowestFree], buffer, BUFFER_SIZE);
	// Update lowestFree
	while(finished==0){
		for (int i=0; i<p_stack->nb_elem; i++) {
			if (counter==p_stack->array[i]) {
				found = 1;
			}
		}
		if (found==0) {
			finished = 1;
			p_stack->lowestFree = counter;
		} else {
			found = 0;
			counter++;
		}
	}
}

void StackPop(STACK *p_stack, char* buffer) {
	memcpy((void *) buffer, (void *) p_stack->stack[p_stack->array[0]], BUFFER_SIZE);
	// UPDATE LOWEST FREE
	if (p_stack->array[0] < p_stack->lowestFree) {
		p_stack->lowestFree = p_stack->array[0];
	}
	for (int i=0; i<p_stack->nb_elem; i++) {
		p_stack->array[i] = p_stack->array[i+1];
	}
	p_stack->array[p_stack->nb_elem] = INT_MAX;
	p_stack->nb_elem--;
}
