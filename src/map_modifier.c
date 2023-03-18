#include <stdlib.h>

#include "prims.h"

char **create_map(coord_t size)
{
    int array_height = size.y * 2 + 1;
    int array_width = size.x * 2 + 1;
    char **map = calloc(array_height, sizeof(char *));

    for (int i = 0; i < array_height; i++) {
        map[i] = calloc(array_width, sizeof(char *));

        if (i % 2 == 0)
            for (int j = 0; j < array_width; j++)
                map[i][j] = 'X';
        else
            for (int j = 0; j < array_width; j += 2)
                map[i][j] = 'X';
    }

    if (array_height % 2 == 0)
        for (int i = 1; i < array_height; i += 2)
            map[i][array_width - 1] = 'X';

    if (array_width % 2 == 0)
        for (int i = 1; i < array_width; i += 2)
            map[array_height - 1][i] = 'X';

    return map;
}

void add_start_finish(char **map, coord_t start, coord_t finish)
{
    map[start.y * 2 + 1][start.x * 2 + 1] = 'S';
    map[finish.y * 2 + 1][finish.y * 2 + 1] = 'F';
}

void free_map(char **map, int height)
{
    int array_height = height * 2 + 1;

    for (int i = 0; i < array_height; i++) {
        free(map[i]);
    }
    free(map);
}

char **add_new_way(char **map, marked_tile_t *tile, int tile_nb)
{
    int dir = 0;

    for (int i = 0; i < tile_nb; i++)
        tile = tile->next;

    dir = tile->cards[rand() % tile->cards_nb];
    map[tile->pos.y * 2 + 1 - CARDS_POS[dir].y][tile->pos.x * 2 + 1 - CARDS_POS[dir].x] = '.';

    map[tile->pos.y * 2 + 1][tile->pos.x * 2 + 1] = '.';

    return map;
}