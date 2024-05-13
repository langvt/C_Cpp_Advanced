#include <stdio.h>
#include <stdint.h>
#include<stdlib.h>
#include <stdbool.h>

typedef struct
{
    uint8_t size;
    int8_t capacity;
    uint8_t *array;
}Stack;

void initStack(Stack *stack, int size)
{
    stack->size = size;
    stack->capacity = -1;
    stack->array = (uint8_t*) malloc(sizeof(uint8_t) *size);
}

bool isFull(Stack stack)
{
    if(stack.capacity == stack.size -1)
    {
        return true;
    }
    else return false;
}

bool isEmpty(Stack stack)
{
    if (stack.capacity == -1)
    {
        return true;

    }
    else return false;
}
void pushStack(Stack *stack, uint8_t value)
{
    if(isFull(*stack))
    {
        printf("stack is full, not add an element\n");
    }
    else{
        stack->array[++ (stack->capacity)]= value;
    }
    
}

void popStack (Stack *stack)
{
    if(isEmpty(*stack))
    {
        printf("stack is empty, not has a element to remove\n");

    }
    else{
        stack->array[stack->capacity --] ='\0';
    }
}
void display(Stack stack)
{
    if(isEmpty(stack))
    {
        printf(" stack is empty, not a value to display\n");
        return;
    }

    printf("the value of elemnt: \n");

    for(int i = 0; i<= stack.capacity; i++ )
    {
        printf("%d ",stack.array[i]);
    }
    printf("\n");
}
uint8_t top(Stack stack)
{
    return stack.array[stack.capacity];
}

uint8_t size(Stack stack)
{
    return stack.capacity +1;
}
int main ()
{
     Stack stack1;
     initStack(&stack1, 5);

     pushStack(&stack1, 12);
     pushStack(&stack1, 1);
     pushStack(&stack1, 5);
     pushStack(&stack1, 6);
     pushStack(&stack1, 9);

    display(stack1);
     printf("value of top: %d\n", top(stack1));
     printf("size of stack: %d\n", size(stack1));

     pushStack(&stack1, 6);

     popStack(&stack1);

     display(stack1);
      printf("value of top: %d\n", top(stack1));
     printf("size of stack: %d\n", size(stack1));
}