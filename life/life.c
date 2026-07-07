#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void    print_map(char **board, int height, int width)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (board[i][j])
                putchar('0');
            else
                putchar(' ');
        }
        putchar('\n');
    }
}
void    free_map(char **board, char **new_board, int height)
{
    for (int i = 0; i < height; i++)
    {
        free(board[i]);
        free(new_board[i]);
    }
    free(board);
    free(new_board);
    board = NULL;
    new_board = NULL;
}
int main(int ac, char **argv)
{
    if (ac != 4)
        return 1;

    int width = atoi(argv[1]);
    int height = atoi(argv[2]);
    int iterations = atoi(argv[3]);
    if (width <= 0 || height <= 0 || iterations < 0)
        return 1;


    char **board = malloc(sizeof(char *) * height);
    char **new_board = malloc(sizeof(char *) * height);
    if (!board || !new_board)
        return 1;
    for (int i = 0; i < height; i++)
    {
        board[i] = calloc(width, sizeof(char));
        new_board[i] = calloc(width, sizeof(char));
        if (!board[i] || !new_board[i])
            return 1;
    }


    int x = 0;
    int y = 0;
    int pen = 0;
    char c;
    while (read(0, &c, 1))
    {
        if (c == 'w' && y > 0)
            y--;
        else if (c == 's' && y < height - 1)
            y++;
        else if (c == 'a' && x > 0)
            x--;
        else if (c == 'd' && x < width - 1)
            x++;
        else if (c == 'x')
            pen = !pen;

        if (pen)
            board[y][x] = 1;
    }


    int i = 0;
    while (i < iterations)
    {
        y = 0;
        while (y < height)
        {
            x = 0;
            while (x < width)
            {
                int dy = -1;
                int d = 0;
                while (dy <= 1)
                {
                    int dx = -1;
                    while (dx <= 1)
                    {
                        if ((dx || dy) && dx + x >= 0 && dx + x < width && dy + y >= 0 && dy + y < height)
                            d += board[dy + y][dx + x];
                        dx++;
                    }
                    dy++;
                }
                if (board[y][x] && (d == 2 || d == 3))
                    new_board[y][x] = 1;
                else if (!board[y][x] && d == 3)
                    new_board[y][x] = 1;
                else
                    new_board[y][x] = 0;
                x++;
            }
            y++;
        }
        for (int r = 0; r < height; r++)
        {
            for (int cc = 0; cc < width; cc++)
                board[r][cc] = new_board[r][cc];
        }
        i++;
    }

    print_map(board, height, width);
    free_map(board, new_board, height);
    return 0;
}