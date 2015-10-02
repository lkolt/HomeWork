#include <stdio.h>
#include <stdlib.h>

int Bang(int x)
{
    int s = (x >> 31);                       // return -1: x < 0; 0: x >= 0;
    int mabsx = ((x & s) | ((~x + 1) & ~s)); // return -x: x >= 0; x: x < 0;
    int res = ((~(mabsx >> 31)) + 2) & 1;
    return res;
}

int main()
{
    int x;
    scanf("%d", &x);
    printf("%d", Bang(x));

    return 0;
}
