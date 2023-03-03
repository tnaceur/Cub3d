#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

int str2d(char **a)
{
    int i;

    i = 0;
    while (a[i])
        i++;
    return i;
}

int main()
{
    char **b;

    b = malloc(sizeof(char*) * 5);
    b[0] = "hello world\n";
    b[1] = "hello world\n";
    b[2] = "hello world\n";
    b[3] = "hello world\n";
    b[4] = NULL;
    if (str2d(b) > 1000 && b[1000] && b[10000][344])
        printf("hello world\n");
}