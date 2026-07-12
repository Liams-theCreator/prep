#include <stdio.h>
#include <stdlib.h>

int min3(int a, int b, int c)
{
    int m = a;
    if (b < m) m = b;
    if (c < m) m = c;
    return m;
}

int process(FILE *f)
{
    (void)f;
    return 0;
}

int main (int ac, char **argv)
{

    if (ac < 2)
    {
        if (process(stdin))
            fprintf(stderr, "map error\n");
        return 0;
    }
    for (int i = 1; i < ac; i++)
    {
        FILE *f = fopen(argv[i], "r");
        if (!f || process(f))
            fprintf(stderr, "map error\n");
        if (f)
            fclose(f);
    }
    return 0;
}