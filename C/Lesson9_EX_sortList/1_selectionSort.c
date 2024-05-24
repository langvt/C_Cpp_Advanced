#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b; 
    *b = temp;
}

void selectionSort(int a[], int soluong)
{
    for(int i = 0; i < soluong-1; i++)
    {
        int min_pos = i;
        for(int j = i+1; j <soluong; j ++)
        {
            if(a[min_pos] > a[j] )
            {
                min_pos = j;
            }
            
        }
       swap( &a[i], &a[min_pos]);
    }
}

void bubleSort(int a[], int soluong)
{
    for (int i = 0 ; i < soluong -1; i ++)
    {
        for (int j = 0; j < soluong -1 -i; j ++)
        {
            if (a[j] > a[j+1])
            {
                swap(&a[j], &a[j+1]);
            }
        }
    }
}

void insertSort(int a[], int soluong)
{
    for(int i = 1; i < soluong; i++)
    {
        int x = a[i], pos = i -1;
        while(pos >= 0 && x < a[pos])
        {
            a[pos+1] = a[pos];
            --pos;
        }
        a[pos+1] = x;
    }
}
int main()
{
    int soluong , a[100];
    printf("nhap so luong phan tu can sap xep: ");
    scanf("%d", &soluong);

    printf("\nnhap cac phan tu: ");
    for(int i = 0 ; i < soluong; i++)
    {
        scanf("%d", &a[i]);
    }

    //selectionSort(a, soluong);
    //bubleSort(a, soluong);
    insertSort(a, soluong);

    printf("cac phan tu sau sap xep: ");
    for(int i = 0 ; i < soluong; i++)
    {
        printf("%d ", a[i]);
    }
    return 0;
}