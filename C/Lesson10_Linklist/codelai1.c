#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct node
{
    uint8_t data;
    struct node *next;
}NODE;

/* create a new node*/
NODE * createnode (uint8_t data)
{
    NODE *newnode = (NODE*) malloc(sizeof(NODE));
    newnode->data = data;
    newnode->next = NULL;
    return newnode;
}

/*loop over link list*/
void loop (NODE* head)
{
    if(head == NULL)
    {
        printf("the link list is empty\n");
    }
    else{
        while (head!=NULL)
        {
            printf("%d ", head ->data);
            head = head ->next;
        }
    }
}

/*push a new node at front of list*/
void pushFront(NODE **  nextHead, uint8_t data)
{
    NODE *newnode = createnode(data);
     newnode ->next = *nextHead;
     *nextHead = newnode;
}

/*push a new node at the end of list*/
void pushEnd(NODE **nextHead, uint8_t data)
{
    NODE * temp = *nextHead;
    NODE *newnode = createnode(data);
    if(*nextHead ==NULL)
    {
        *nextHead = newnode;
    }
    else
    {
        while (temp ->next!=NULL)

        {
            temp = temp ->next;
        }
        temp ->next = newnode;
    }
}
/*insert a new node at any where of list*/
void insertNode(NODE **nextHead, uint8_t data, uint8_t pos)
{
    NODE*newnode = createnode(data);
    NODE *temp = *nextHead;
    uint8_t count = 0;
    if(temp == NULL || pos == 0)
    {
        newnode ->next = temp;
        *nextHead  = newnode;
        return;
    }
    else if (pos < 0)
    {
        printf("error this position\n");
        return;
    }

    else {
        printf("insert node at position %d with value is %d\n", pos, data);

        while (temp ->next != NULL && count < pos -1)
        {
            temp = temp ->next;
            count ++;
        }

        newnode ->next = temp ->next;
        temp ->next = newnode;
        
    }
    
}
/*pop a node at the fron of list*/
void popFront(NODE ** nexthead)
{
    
    NODE * temp = *nexthead;
    if(temp == NULL)
    {
        printf("the list is empty, not has a node to pop\n");
        return;
    }
    *nexthead = temp ->next;
    free(temp);
}
/*pop a node at the end of list*/
void popEnd(NODE ** nextHead)
{
    NODE* temp = *nextHead;
    if(temp == NULL)
    {
        printf("the list is empty, nos has a node to pop\n");
        return;
    }
    else if(temp ->next == NULL)
    {
        *nextHead = temp ->next;
        free(temp);
    }
    else{
        while (temp ->next ->next != NULL)
        {
            temp = temp ->next;
        }

        free(temp ->next);
        temp ->next = NULL;

    }
}
/*remove a node at any where of list*/
void removeNode(NODE **nextHead, uint8_t pos)
{
    NODE * temp = *nextHead;
    NODE *remove;
    uint8_t count = 0;

    if (temp == NULL)
    {
        printf (" the list is empty, not has a node to remove\n");
        return;
    }
    else if ( pos == 0)
    {
        *nextHead = temp ->next;
        free (temp);
        return;
    }

    
    while (temp ->next != NULL && count < pos - 1)
        {
            temp = temp ->next;
            count ++;
        }

    if(temp ->next == NULL || count < pos -1)
        {
            printf(" position %d is error remove\n", pos);
            return;
        }
     else{
            remove  = temp ->next;
            temp -> next = remove ->next;
            free(remove);

        }
    

}
/* return value of the front of list*/
uint8_t frontData(NODE *nextHead)
{
    if(nextHead == NULL)
    {
        printf("the list is empty, not get value of node at front list\n");
        return 0;
    }
    else{
        return nextHead ->data;
    }
}
/*return value of the end of list*/
uint8_t endValue(NODE *nextHead)
{
    NODE *temp = nextHead;
    if(nextHead == NULL)
    {
        printf("the list is empty, not get value of node at end list\n");
        return 0;
    }
    else{
        while (temp ->next !=NULL)
        {
            temp = temp ->next;

        }

        return temp ->data;
    }
}
/*return value at any where of the list*/
uint8_t anyValue (NODE *nextHead, uint8_t pos)
{
    NODE*temp = nextHead;
    uint8_t count =0;

     if(nextHead == NULL)
    {
        printf("the list is empty, not get value of node in list\n");
        return 0;
    }
    if (pos < 0)
    {
        printf("error position\n");
        return 0;
    }
    else{
        while (temp ->next != NULL && count < pos)
        {
            temp = temp ->next;
            count ++;
        }
        return temp ->data;
        
    }

}
/* return the size of list*/
uint8_t sizeList(NODE *nextHead)
{
    int count = 0;
    if(nextHead == NULL)
    {
        printf("the list is empty, not get the size\n");
        return 0;
    }
    else 
    {
         while (nextHead != NULL)
         {
            count ++;
            nextHead = nextHead ->next;
         }
     return count;    
    }
}
int main()
{
    NODE *head = NULL;
    int pos = 3;
    // pushFront(&head, 1);
    // pushFront(&head, 2);
    // pushFront(&head, 3);
    // pushFront(&head, 4);
    // pushEnd(&head, 5);

    for(int i = 0; i < 10; i ++)
    {
        pushEnd(&head, i);
    }
    insertNode(&head, 4, 5);
    loop(head);

    printf("\n");

    //popFront(&head);
    //popEnd(&head);
    removeNode(&head, 5);

    loop(head);

    printf("\n");

    printf("\nthe size of list: %d\n", sizeList(head));
    printf("\nthe value of front node: %d\n",frontData(head));
    printf("the value of node at end list: %d\n", endValue(head));
    printf("the value of position %d: %d\n", pos ,anyValue(head, pos));
    
}