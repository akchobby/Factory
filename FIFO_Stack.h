#ifndef FIFO_STACK_HEADER
#define FIFO_STACK_HEADER

#define CAPACITY 20

typedef struct STACK {
	char* stack[CAPACITY];
	int lowestFree;
	int nb_elem;
	int array[CAPACITY]; 

} STACK;

void StackInit(STACK *p_stack);
void StackPush(STACK *p_stack, char* buffer);
void StackPop(STACK *p_stack, char* buffer);

#endif
