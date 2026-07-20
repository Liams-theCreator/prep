#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_map
{
    int rows;
    int cols;
    char empty;
    char obstacles;
    char full;
    char **grid;
} t_map;

void free_grid(t_map *m, int n)
{
    if (!m->grid)
        return;
    while (n-- > 0)
        free(m->grid[n]);
    free(m->grid);
    m->grid = NULL;
}

int valid_char(t_map *m, char c)
{
    return (c == m->obstacles || c == m->empty);
}

int min3(int a, int b, int c)
{
    int m = a;
    if (b < m)
        m = b;
    if (c < m)
         m = c;
    return m;
}

int ft_atoi(char *str)
{
    int i = 0, sign = 1, res = 0;
    while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
        i++;
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-') sign = -1;
        i++;
    }
    while (str[i] >= '0' && str[i] <= '9')
    {
        res = res * 10 + (str[i] - '0');
        i++;
    }
    return (res * sign);
}

int ft_strlen(char *str)
{
    int i = 0;
    while (str[i]) i++;
    return (i);
}

int parse_header(FILE *f, t_map *m)
{
    char *line = NULL;
    size_t cap = 0;
    int length;

    if (getline(&line, &cap, f) == -1)
        return (free(line), 0);

    length = ft_strlen(line);
    if (length < 5 || line[length - 1] != '\n')
        return (free(line), 0);

    m->empty = line[length - 4];
    m->obstacles = line[length - 3];
    m->full = line[length - 2];
    line[length - 4] = '\0';
    m->rows = ft_atoi(line);
    free(line);

    if (m->rows <= 0)
        return (0);
    if (m->empty == m->obstacles || m->empty == m->full || m->obstacles == m->full)
        return (0);
    return (1);
}

int parse_map(FILE *f, t_map *m)
{
    char *line = NULL;
    size_t cap = 0;

    m->grid = malloc(sizeof(char *) * m->rows);
    if (!m->grid)
        return (0);

    int i = 0;
    while (i < m->rows)
    {
        if (getline(&line, &cap, f) == -1)
            return (free(line), free_grid(m, i), 0);

        int j = 0;
        while (line[j] && line[j] != '\n')
            j++;

        if (i == 0)
            m->cols = j;
        if (j != m->cols)
            return (free(line), free_grid(m, i), 0);

        m->grid[i] = malloc(j + 1);
        if (!m->grid[i])
            return (free(line), free_grid(m, i), 0);

        for (int j = 0; line[j] && line[j] != '\n'; j++)
        {
            if (!valid_char(m, line[j]))
                return (free(line), free_grid(m, i + 1), 0);
            m->grid[i][j] = line[j];
        }
        m->grid[i][j] = '\0';
        i++;
    }
    free(line);
    return (1);
}

void solve(t_map *m)
{
    int best = 0;
    int max_i = 0;
    int max_j = 0;
    int **dp;

    dp = malloc(sizeof(int *) * m->rows);
    if (!dp)
        return ;
    for (int i = 0; i < m->rows; i++)
    {
        dp[i] = calloc(m->cols, sizeof(int));
        if (!dp[i])
        {
            while (i-- > 0)
                free(dp[i]);
            return (free(dp));
        }
    }

    for (int i = 0; i < m->rows; i++)
    {
        for (int j = 0; j < m->cols; j++)
        {
            if (m->grid[i][j] == m->obstacles)
                dp[i][j] = 0;
            else if (m->grid[i][j] == m->empty)
            {
                if (i == 0 || j == 0)
                    dp[i][j] = 1;
                else
                    dp[i][j] = 1 + min3(dp[i][j - 1], dp[i - 1][j], dp[i - 1][j - 1]);
            }
            if (dp[i][j] > best)
            {
                best = dp[i][j];
                max_i = i;
                max_j = j;
            }
        }
    }

    for (int i = max_i - best + 1; i <= max_i; i++)
        for (int j = max_j - best + 1; j <= max_j; j++)
            m->grid[i][j] = m->full;

    for (int i = 0; i < m->rows; i++)
        fprintf(stdout, "%s\n", m->grid[i]);
    
    for (int i = 0; i < m->rows; i++)
        free(dp[i]);
    free(dp);
}

int main(int ac, char **av)
{
    t_map m;

    if (ac == 1)
    {
        if (!parse_header(stdin, &m) || !parse_map(stdin, &m))
            return (fprintf(stderr, "error map\n"), 1);
        solve(&m);
        free_grid(&m, m.rows);
        return 0;
    }
    for (int i = 1; i < ac; i++)
    {
        FILE *f = fopen(av[i], "r");
        if (!f || !parse_header(f, &m) || !parse_map(f, &m))
        {
            fprintf(stderr, "error map\n");
            if (f)
                fclose(f);
            return 1;
        }
        solve(&m);
        free_grid(&m, m.rows);
        if (i < ac - 1)
            fprintf(stdout, "\n");
        fclose(f);
    }
    return 0;
}
