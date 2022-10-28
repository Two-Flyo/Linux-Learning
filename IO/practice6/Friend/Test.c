#include "add.h"
#include "sub.h"

int main()
{
    int a = 10;
    int b = 5;
    int ret1 = add(a, b);
    int ret2 = sub(a, b);
    printf("a+b=%d a-b=%d", ret1, ret2);
    return 0;
}