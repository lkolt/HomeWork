#include <stdio.h>
#include <stdlib.h>

int bang(int x)
{
    int res = ((~((x << 31) >> 31)) + 2) & 1;
    return res;
}

int main()
{
    int x;
    scanf("%d", &x);
    printf("%d", bang(x));
    return 0;
}
