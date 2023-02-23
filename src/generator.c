#include <time.h>
#include <stdlib.h>

#include "generator.h"


const pos_t CARDS_POS[4] = {{0, -1}, {0, 1}, {1, 0}, {-1, 0}};


static char **create_map(pos_t size)
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

    map[1][0] = 'S';
    map[array_height - 2][array_width - 1] = 'F';

    return map;
}

static marked_tile_t *remove_marked_tile(marked_tile_t *tile, int tile_nb)
{
    marked_tile_t *first = tile;
    marked_tile_t *new_next = NULL;

    if (tile_nb == 0) {
        first = tile->next;
        free(tile);
    } else {
        for (int i = 0; i < tile_nb - 1; i++)
            tile = tile->next;
        new_next = tile->next->next;
        free(tile->next);
        tile->next = new_next;
    }

    return first;
}

static marked_tile_t *mark_tile(pos_t pos, enum cards card)
{
    marked_tile_t *new_tile = malloc(sizeof(marked_tile_t));

    new_tile->pos = pos;
    new_tile->cards[0] = card;
    new_tile->cards_nb = 1;
    new_tile->next = NULL;

    return new_tile;
}

static void add_marked_tile(marked_tile_t *tile, pos_t pos, enum cards card)
{
    marked_tile_t *new_tile = mark_tile(pos, card);

    for (; tile->next; tile = tile->next);
    tile->next = new_tile;
}

static void add_cardinal(marked_tile_t *tile, pos_t pos, enum cards card)
{
    for (; tile->pos.x != pos.x || tile->pos.y != pos.y; tile = tile->next);

    tile->cards[tile->cards_nb] = card;
    tile->cards_nb++;
}

static bool check_tile_pos(pos_t pos, pos_t size)
{
    if (pos.y < 0 || pos.y >= size.y)
        return false;
    if (pos.x < 0 || pos.x >= size.x)
        return false;
    return true;
}

static int mark_tiles_around(char **map, marked_tile_t *tile, int tile_nb, pos_t size)
{
    marked_tile_t *first = tile;
    int marked_tile_nb = 0;
    pos_t to_mark;

    for (int i = 0; i < tile_nb; i++)
        tile = tile->next;

    to_mark = tile->pos;

    for (int i = 0; i < 4; i++) {
        to_mark.y += CARDS_POS[i].y;
        to_mark.x += CARDS_POS[i].x;
        if (check_tile_pos(to_mark, size))
            switch (map[to_mark.y * 2 + 1][to_mark.x * 2 + 1]) {
            case '\0':
                marked_tile_nb++;
                add_marked_tile(tile, to_mark, i);
                map[to_mark.y * 2 + 1][to_mark.x * 2 + 1] = '*';
                break;
            case '*':
                add_cardinal(first, to_mark, i);
                break;
            }
        to_mark = tile->pos;
    }

    return marked_tile_nb;
}

static char **add_new_way(char **map, marked_tile_t *tile, int tile_nb)
{
    int dir = 0;

    for (int i = 0; i < tile_nb; i++)
        tile = tile->next;

    dir = tile->cards[rand() % tile->cards_nb];
    map[tile->pos.y * 2 + 1 - CARDS_POS[dir].y][tile->pos.x * 2 + 1 - CARDS_POS[dir].x] = '.';

    map[tile->pos.y * 2 + 1][tile->pos.x * 2 + 1] = '.';

    return map;
}

static char **prims_loop(char **map, pos_t size)
{
    int random_tile = 0;
    marked_tile_t *tile = malloc(sizeof(marked_tile_t));
    int tiles_nb = 0;

    tile->next = NULL;
    tile->pos = (pos_t){rand() % size.x, rand() % size.y};
    map[tile->pos.y * 2 + 1][tile->pos.x * 2 + 1] = '.';
    tiles_nb += mark_tiles_around(map, tile, random_tile, size);
    tile = remove_marked_tile(tile, 0);


    while (tiles_nb > 0) {
        random_tile = rand() % tiles_nb;
        map = add_new_way(map, tile, random_tile);
        tiles_nb += mark_tiles_around(map, tile, random_tile, size);
        tile = remove_marked_tile(tile, random_tile);
        tiles_nb--;
    }

    return map;
}

char **generator(pos_t size)
{
    char **map = create_map(size);

    srand(time(0));
    map = prims_loop(map, size);

    return map;
}