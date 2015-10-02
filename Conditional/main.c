#include <stdio.h>
#include <stdlib.h>

int conditional(int x, int y, int z)
{
    int check = (!x + ~0); // ~0 == -1
    int res = ((check & y) | (~check & z));
    return res;
}

int main()
{
    int x, y, z;
    scanf("%d %d %d", &x, &y, &z);
    printf("%d", conditional(x, y, z));
    return 0;
}
