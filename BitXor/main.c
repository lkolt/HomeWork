#include <stdio.h>
#include <stdlib.h>

int bitOr(int x, int y) // ~((~x)&(~y));
{
    int ax = ~x;
    int ay = ~y;
    int ares = ax & ay;
    int res = ~ares;
    return res;
}

int bitXor(int x, int y) // (((~x) & y)|(x & (~y)))
{
    int ax = ~x;
    int ay = ~y;
    int res1 = ax & y;
    int res2 = x & ay;
    int res = bitOr(res1, res2);
    return res;
}

int main()
{

    int x, y;
    scanf("%d %d", &x, &y);
    printf("%d", bitXor(x, y));
    return 0;
}
