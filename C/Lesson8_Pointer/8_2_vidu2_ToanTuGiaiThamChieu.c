#include <stdio.h>

void tang1 (int a){
    printf("gia tri cua a trong ham tang1: %d\n", a);
    a += 100;
    printf("gia tri cua a trong tang1 sau khi thuc hien: %d\n", a);
    
}

void tang2(int *a){
    printf("gia tri cua a truoc khi thuc hien tang2: %d\n", *a);
    *a += 100;
    
}
int main(int argc, char const *argv[])
{
    int a = 300;

    tang1(a);
    printf("giá trị của a sau khi tang1 ket thuc: %d \n", a);

    tang2(&a);
    printf("gia tri của a sau khi tang2 kết thúc: %d \n", a);
    return 0;
}
