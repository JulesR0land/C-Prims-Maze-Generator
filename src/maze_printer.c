#include <stdio.h>

#include "prims.h"

void print_maze(char **map, coord_t size)
{
    int array_height = size.y * 2 + 1;
    int array_width = size.x * 2 + 1;

    for (int i = 0; i < array_height; i++) {
        for (int j = 0; j < array_width; j++)
            if (map[i][j] == '.')
                printf(" ");
            else
                printf("%c", map[i][j]);
        printf("\n");
    }
}