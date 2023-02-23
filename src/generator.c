#include <time.h>
#include <stdlib.h>

#include "generator.h"

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