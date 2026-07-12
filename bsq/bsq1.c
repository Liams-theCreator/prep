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
    int  h = 0, w = 0, i, j;
    char e, o, fu;
    char *hdr = NULL;
    size_t cap = 0;
    ssize_t n;


    n = getline(&hdr, &cap, f);
    if (n < 5 || hdr[n - 1] != '\n') {
        free(hdr);
        return 1;
    }
    e  = hdr[n - 4];
    o  = hdr[n - 3];
    fu = hdr[n - 2];

    for (i = 0; i < n - 4; i++)
    {
        if (hdr[i] < '0' || hdr[i] > '9')
        {
            free(hdr);
            return 1;
        }
        h = h * 10 + (hdr[i] - '0');
    }
    free(hdr);
    if (h <= 0 || e == o || e == fu || o == fu)
        return 1;



    char **map = malloc(sizeof(char *) * h);
    for (i = 0; i < h; i++)
    {
        char *line = NULL;
        size_t c = 0;
        if (getline(&line, &c, f) < 0)
            return 1;
        j = 0;
        while (line[j] && line[j] != '\n')
            j++;
        line[j] = '\0';
        if (i == 0)
            w = j;
        if (j == 0 || j != w)
            return 1;
        map[i] = line;
    }

    int dp[h][w];
    int max = 0, mi = 0, mj = 0;
    for (i = 0; i < h; i++) 
    {
        for (j = 0; j < w; j++) 
        {
            if (map[i][j] == o)
                dp[i][j] = 0;
            else if (map[i][j] == e) 
            {
                if (i == 0 || j == 0)
                    dp[i][j] = 1;
                else
                    dp[i][j] = 1 + min3(dp[i-1][j], dp[i][j-1], dp[i-1][j-1]);
            } else
                return 1;
            if (dp[i][j] > max) 
            {
                max = dp[i][j];
                mi = i;
                mj = j;
            }
        }
    }


    for (i = mi - max + 1; i <= mi; i++)
        for (j = mj - max + 1; j <= mj; j++)
            map[i][j] = fu;
    for (i = 0; i < h; i++) 
    {
        fprintf(stdout, "%s\n", map[i]);
        free(map[i]);
    }
    free(map);
    return 0;
}

int main(int ac, char **av)
{
    if (ac < 2) 
    {
        if (process(stdin))
            fprintf(stderr, "map error\n");
        return 0;
    }
    for (int i = 1; i < ac; i++) 
    {
        FILE *f = fopen(av[i], "r");
        if (!f || process(f))
            fprintf(stderr, "map error\ns");
        if (f)
            fclose(f);
    }
    return 0;
}
