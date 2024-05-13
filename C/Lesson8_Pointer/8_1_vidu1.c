#include <stdio.h>

int a = 10;

void tong(){
    printf("hello\n");
}

int main(int argc, char const *argv[])
{
    int *ptr = &a;
    *ptr = 27;

    printf("dia chi cua a: %p\n", ptr);

    printf("gia tri a: %d\n", a);

    printf("gia tri cua bien ma ptr tro toi: %d\n", *ptr);

    printf("dia chi cua tong: %p\n", ptr);
    printf("size off pointer: %d bytes\n", sizeof(ptr) );
    return 0;
}
