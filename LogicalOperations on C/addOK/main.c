#include <stdio.h>
#include <stdlib.h>

int addOK(int x, int y)
{
    int res = !(~((x >> 31) ^ (y >> 31)) & ((x >> 31) ^ ((x + y) >> 31)));
    return res;
}

int main()
{
    int x, y;
    scanf("%d %d", &x, &y);
    printf("%d", addOK(x, y));
    return 0;
}
