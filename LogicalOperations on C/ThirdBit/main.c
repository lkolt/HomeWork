#include <stdio.h>
#include <stdlib.h>

int thirdBit() // 00100100...100100
{
    int res = 4; // 100
    res = (res << 3) | res; // 100000 | 100 = 100100
    res = (res << 6) | res; // 100100100100
    res = (res << 12) | res; // ...
    res = (res << 6) + 36; // ...100100000000 + 100100
    return res;
}


int main()
{
    printf("%d", thirdBit());
    return 0;
}
