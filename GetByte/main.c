#include <stdio.h>
#include <stdlib.h>

int getByte(int x, int n)
{
    return ((x & ((1 << n) >> 1)) << 1) >> n;
}

int main()
{
    int x, n;
    scanf("%d %d", &x, &n);
    printf("%d", getByte(x, n));
    return 0;
}
