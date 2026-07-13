#include <stdio.h>
#include <stdlib.h>

typedef struct s_map 
{
    int    rows;
    int    cols;
    char   empty;
    char   obstacle;
    char   full;
    char **grid;
}   t_map;

int min3(int a, int b, int c)
{
    int m = a;
    if (b < m) m = b;
    if (c < m) m = c;
    return m;
}

void free_grid(t_map *m, int n)
{
    if (!m->grid)
        return;
    while (n-- > 0)
        free(m->grid[n]);
    free(m->grid);
    m->grid = NULL;
}

int printable(char c) 
{ 
    return c >= 32 && c <= 126; 
}

int parse_header(FILE *f, t_map *m)
{
    if (fscanf(f, "%i %c %c %c", &m->rows, &m->empty, &m->obstacle, &m->full) != 4)
        return 0;
    if (m->rows < 1 || m->empty == m->obstacle || m->empty == m->full || m->obstacle == m->full)
        return 0;
    if (!printable(m->empty) || !printable(m->obstacle) || !printable(m->full))
        return 0;
    return 1;
}

int parse_map(FILE *f, t_map *m)
{
    char   *line = NULL;
    size_t  cap = 0;
    ssize_t n;
    int     i, j;

    getline(&line, &cap, f);
    m->cols = -1;
    m->grid = calloc(m->rows, sizeof(char *));
    if (!m->grid)
        return (free(line), 0);
    for (i = 0; i < m->rows; i++)
    {
        n = getline(&line, &cap, f);
        if (n < 1)
            return (free(line), free_grid(m, i), 0);
        if (line[n - 1] == '\n' || line[n - 1] == '\r')
            line[--n] = '\0';
        if (m->cols == -1)
            m->cols = n;
        if (n != m->cols)
            return (free(line), free_grid(m, i), 0);
        m->grid[i] = malloc(m->cols + 1);
        if (!m->grid[i])
            return (free(line), free_grid(m, i), 0);
        for (j = 0; j < m->cols; j++)
        {
            if (line[j] != m->empty && line[j] != m->obstacle && line[j] != m->full)
                return (free(line), free_grid(m, i + 1), 0);
            m->grid[i][j] = (line[j] == m->full) ? m->empty : line[j];
        }
        m->grid[i][m->cols] = '\0';
    }
    free(line);
    return 1;
}

void solve(t_map *m)
{
    int best = 0, br = 0, bc = 0, i, j;
    int dp[m->rows][m->cols];

    for (i = 0; i < m->rows; i++)
        for (j = 0; j < m->cols; j++) 
        {
            if (m->grid[i][j] == m->obstacle)
                dp[i][j] = 0;
            else if (i == 0 || j == 0)
                dp[i][j] = 1;
            else
                dp[i][j] = min3(dp[i-1][j], dp[i][j-1], dp[i-1][j-1]) + 1;
            if (dp[i][j] > best) 
            {
                best = dp[i][j];
                br = i - best + 1;
                bc = j - best + 1;
            }
        }
    for (i = br; i < br + best; i++)
        for (j = bc; j < bc + best; j++)
            m->grid[i][j] = m->full;
    for (i = 0; i < m->rows; i++)
        fprintf(stdout, "%s\n", m->grid[i]);
}

void process(FILE *f)
{
    t_map m;
    m.grid = NULL;
    if (!parse_header(f, &m) || !parse_map(f, &m)) 
    {
        fprintf(stderr, "map error\n");
        return;
    }
    solve(&m);
    free_grid(&m, m.rows);
}

int main(int ac, char **av)
{
    int i = 1;

    if (ac < 2)
        return (process(stdin), 0);
    while (i < ac) 
    {
        FILE *f = fopen(av[i], "r");
        if (!f)
            fprintf(stderr, "map error\n");
        else 
        {
            process(f);
            fclose(f);
        }
        if (i + 1 < ac)
            fprintf(stdout, "\n");
        i++;
    }
    return 0;
}
