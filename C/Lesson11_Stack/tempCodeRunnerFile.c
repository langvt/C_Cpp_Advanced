#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct stack
{
    int *item;
    int top;
    int size;
}Stack;

/*init the stach*/
void initStack(Stack *stack, int size)
{
    stack ->item = (int*) malloc(size *sizeof(int));
    stack ->size = size;
    stack ->top =  -1;
}

/*check stack is empty*/
int isEmpty(Stack stack)
{
    return stack .top = -1;
}

/*check stack is full*/
int isFull(Stack stack)
{
    return stack.top = stack.size -1;
}

/*push stack*/
void push(Stack *stack, int value)
{
    if(isFull(*stack))
    {
        printf("stack is full\n");
        return;
    }
    else{
        stack->item[++ stack ->top] = value;
    }
}

/*pop stack*/
void pop_stack(Stack *stack)
{
    if(isEmpty(*stack))
    {
        printf("stack is Empty \n");
        return;
    }
    else{
         stack->item[stack->top --];
    }
}

/*return value at top of the stack*/
int peek_top(Stack stack)
{
    if(isEmpty(stack))
    {
        printf("stack is empty\n");
    }
    else{
        return stack.item[stack.top];
    }

}

/*check size of stack*/
int size_stack(Stack stack)
{
    if(isEmpty(stack))
    {
        printf("stack is empty\n");
        return 0;
    }
    else{
        return stack.top + 1;
    }
}
int main ()
{
    Stack stack1;
    initStack(&stack1, 5);

    push(&stack1, 2);
    push(&stack1, 4);
    push(&stack1, 5);
    push(&stack1, 7);
    push(&stack1, 9);

    printf("the size of stack is: %d\n", size_stack(stack1));
}