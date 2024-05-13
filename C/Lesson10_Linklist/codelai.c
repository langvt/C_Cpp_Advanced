#include  <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/* */
typedef struct node
{
    int value;
    struct node *next;
}NODE;

/*crate a new node*/
NODE *creatnode (int value)
{
    NODE *newnode = (NODE*) malloc(sizeof(NODE));
    newnode ->next = NULL;
    newnode ->value = value;
    return newnode;
}

/*loop over a node */
void loop (NODE *head)
{
    if(head == NULL)
    {
        printf("\nthe list is empty\n");
        return;
    }
    while (head != NULL)
    {
        printf("%d ", head->value);
        head = head->next;
    }
}

/*add a new node a front of link list node*/

void pushFront(NODE **nextHead, int value)
{
    NODE *newnode = creatnode(value);
    if(*nextHead == NULL)
    {
        *nextHead = newnode;
    }
    else 
    {
        newnode ->next = *nextHead;
        *nextHead = newnode;
    }
}

NODE *push_front(NODE *nextHead, int value)
{
    NODE *newnode = creatnode(value);
    if(nextHead == NULL)
    {
        nextHead = newnode;
        return nextHead;
    }
    else{
        newnode ->next = nextHead;
        nextHead = newnode;
        return nextHead;
    }
}

/*add a new node at the end of the link list node*/

void pushEnd(NODE ** nextHead, int value)
{
    NODE *newnode = creatnode(value);
    NODE *temp = *nextHead;

    if (*nextHead == NULL)
    {
        *nextHead = newnode;
        return;
    }
    else{
        while (temp ->next != NULL)
        {
            temp = temp ->next;
        }
        temp ->next = newnode;
    }
}

NODE *push_end (NODE *nextHead, int value)
{
    NODE * newnode = creatnode (value);
    NODE *temp = nextHead;

    if(nextHead == NULL)
    { 
        nextHead = newnode;
    return nextHead;
    }
    else{
        while (temp ->next != NULL)
        {
            temp = temp ->next;
        }
        temp ->next = newnode;

        return nextHead;
    }
    
}

void popFront(NODE ** nextHead)
{
    if(*nextHead == NULL)
    {
    printf("dont have any node to pop\n ");
    return;
    }
    else
    {
        NODE *temp = *nextHead;
        *nextHead = (*nextHead) ->next;

        free(temp);
    }
}

void popEnd (NODE **nextHead)
{
/*in case dont have any node */
    if(*nextHead == NULL)
    {
        printf("dont any node to remove \n");
        return;
    }

/*in case there is a node in the list*/
    else if((*nextHead) ->next == NULL)
    {
        
        free(*nextHead);
        *nextHead = NULL;
        return;
    }
    else{
        NODE *temp = *nextHead;
        while (temp ->next ->next != NULL)
        {
            temp = temp ->next;
        }
        // remove node at end
        free(temp ->next);
        temp ->next = NULL;
    }
}

/*return value at the front of the list*/
uint8_t valueFront(NODE ** nextHead)
{
    if(*nextHead == NULL)
    {
        printf("the list is empty\n");
        return 0;
    }
    else{
        return (*nextHead) ->value;
    }
}

/*return value at the end node of the list*/

uint8_t valueEnd(NODE ** nextHead)
{
    NODE *temp = *nextHead;

    if(*nextHead == NULL)
    {
        printf("the list is empty\n");
        return 0;
    }

    while( temp ->next != NULL)
    {
        temp = temp ->next;
    }

    return temp ->value;
}

/*return valua of any node in the list*/
int returnValue(NODE **nexthead, int pos)
{
    NODE *temp = *nexthead;
    NODE *p;
    int count = 0;

     if(*nexthead == NULL || pos < 0)
    {
        printf("the list is empty\n");
        return 0;
    }

    if(pos == 0){
        return temp ->value;
    }

    while (temp ->next != NULL && count < pos -1)
    {
        temp = temp -> next;
        count ++;
    }
    p = temp ->next;
    return p->value;
    
}

/* insert a node at any where at list*/

void insertNode(NODE **nexthead, int pos, int value)
{

    NODE *newnode = creatnode(value);
     
    NODE *temp = *nexthead;
    int count = 0;

    if(pos < 0)
    {
        printf("error position!\n");
        return;
    }

    if(*nexthead == NULL || pos == 0)
    {
        newnode ->next = *nexthead;
        *nexthead = newnode;
        return;
    }

    while (temp ->next != NULL && count < pos -1)
    {
        temp = temp ->next;
        count ++;
    }
    newnode ->next = temp ->next ;
    temp ->next = newnode;
}

/*remove any node in the list*/
void removeNode(NODE ** nextHead, int pos)
{

    NODE * temp = *nextHead;
    NODE *remove = NULL;
    int count = 0;
    if(*nextHead == NULL)
    {
        printf("the list is empty\n");
        return;
    }

    if(pos < 0 )
    { 
        printf("this position error\n");
    }

    if(pos == 0)
    {
        *nextHead = temp ->next;
        free(temp);
        return;
    }

    while (temp -> next != NULL && count < pos -1 )
    {
        temp = temp -> next;
        count ++;
    }
    remove = temp ->next;
    temp ->next = temp ->next ->next;
    free(remove);
    
}

/* return the size of list*/
int getsize(NODE **nextHead)
{
    int count = 0;
    NODE *temp = *nextHead;

    if(*nextHead == NULL)
    {
        printf("the list is empty\n");
        return 0;
    }

    while (temp != NULL)
    {
        count ++;
        temp = temp ->next;
        
    }
    return count; 
}

int main()
{
    NODE *head = NULL;

    for(int i = 0 ; i <10 ; i++)
    {
        //pushFront(&head, i);
         //head = push_front(head, i);
        pushEnd(&head, i);
        //head = push_end(head, i);
    }

    //popFront(&head);
    //popEnd(&head);
    
    loop (head);

    printf("\nvalue at the front of list: %d\n" ,valueFront(&head));
    printf("the value of the node at the end list: %d\n", valueEnd(&head));

    insertNode(&head, 4, 8);
    loop(head);

    printf("\n");

    removeNode(&head, 5);
    loop(head);

    int pos = 4;
    printf("\nvalue of node %d: %d\n ", pos, returnValue(&head, pos));

    printf("the size of list: %d", getsize(&head));
return 0;
}