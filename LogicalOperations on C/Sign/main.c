#include <stdio.h>
#include <stdlib.h>

int sign(int x)
{
    int res = (x >> 31) | (!!x);
    return res;
}

int main()
{
    int x;
    scanf("%d", &x);
    printf("%d", sign(x));

    return 0;
}
