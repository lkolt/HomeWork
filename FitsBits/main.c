#include <stdio.h>
#include <stdlib.h>

int FitsBits(int x, int n)
{
    int s = (x >> 31);                           // return -1: x < 0; 0: x >= 0;
    int absx = ((x & ~s) | ((~x + 1) & s));      // return x: x >= 0; -x: x < 0;
    int res = !(((absx + (~0 & s)) << 1) >> n);  // return ans;
    return res;
}

int main()
{
    int x, n;
    scanf("%d %d", &x, &n);
    printf("%d", FitsBits(x, n));

    return 0;
}
