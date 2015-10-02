#include <stdio.h>
#include <stdlib.h>

int bitAnd(int x, int y) // res = ~((~x) | (~y));
{
    int ax = ~x;
    int ay = ~y;
    int ares = ax | ay;
    int res = ~ares;
    return res;
}

int main()
{

    int x, y;
    scanf("%i %i", &x, &y);
    printf("%i", bitAnd(x, y));

    return 0;
}
