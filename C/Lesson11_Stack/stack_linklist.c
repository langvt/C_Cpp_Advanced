#include <stdio.h>
#include<stdint.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *next;
}NODE;

NODE *creatNode(int data)
{
    NODE* newnode = (NODE*) malloc(sizeof(NODE));
    newnode ->data = data;
    newnode ->next = NULL;
    return newnode;
}

typedef struct stack
{
    NODE *top;
}STACK;

STACK *creatStack()
{
    STACK *stack = (STACK*) malloc(sizeof(STACK));
    stack->top = NULL;
    return stack;
}

int isEmpty(STACK *stack)
{
    return stack->top == NULL;
}

void pushStack(STACK *stack, int data)
{
    NODE *newnode = creatNode(data);
    stack->top = newnode;
}

int popStack(STACK *stack)
{
    if(isEmpty(stack))
    {
        printf("stack is empty\n");
    return 0; 
    }
    NODE *temp = stack->top;
    int popvalue = temp ->data;
    stack->top = temp ->next;
    free(temp);
    return popvalue;
}

int peek(STACK *stack)
{
    if(isEmpty(stack))
    {
        printf("stack is empty\n");
        return 0;
    }
    return stack->top->data;
}

int main ()
{
    STACK *stack1 = creatStack();

    pushStack(stack1, 1);
    pushStack(stack1, 3);
    pushStack(stack1, 7);
    
    printf("Top element of stack: %d\n", peek(stack1));
    printf("Popped element: %d\n", popStack(stack1));
    printf("Top element of stack after pop: %d\n", peek(stack1));


}
