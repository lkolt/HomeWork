#include <stdio.h>
#include <stdlib.h>

int logicalShift(int x, int n)
{
    int res = ((x & ~(1 << 31)) >> n) | ((x >> 31) & (1 << (31 + (~n + 1))));
    return res;
}

int main()
{
    int x, n;
    scanf("%d %d", &x, &n);
    printf("%d", logicalShift(x, n));
    return 0;
}
