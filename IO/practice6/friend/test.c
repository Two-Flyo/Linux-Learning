#include "sub.h"
#include "add.h"
int main()
{
    int x = 1;
    int y = 2;
    int r1 = add(x, y);
    int r2 = sub(x, y);
    printf("r1=%d r2=%d", r1, r2);
    return 0;
}