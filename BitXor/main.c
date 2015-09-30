#include <stdio.h>
#include <stdlib.h>

int BitOr(int x, int y) // ~((~x)&(~y));
{
    int ax = ~x;
    int ay = ~y;
    int ares = ax & ay;
    int res = ~ares;
    return res;
}

int BitXor(int x, int y) // (((~x) & y)|(x & (~y)))
{
    int ax = ~x;
    int ay = ~y;
    int res1 = ax & y;
    int res2 = x & ay;
    int res = BitOr(res1, res2);
    return res;
}

int main()
{

    int x, y;
    scanf("%d %d", &x, &y);
    printf("%d", BitXor(x, y));
    return 0;
}
