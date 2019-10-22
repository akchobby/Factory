#ifndef FIFO_STACK_HEADER
#define FIFO_STACK_HEADER

typedef struct STACK STACK;

void StackInit(STACK *p_stack);
void StackPush(STACK *p_stack, char* buffer);
void StackPop(STACK *p_stack, char* buffer);

#endif
