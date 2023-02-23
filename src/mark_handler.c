#include <stdlib.h>

#include "generator.h"

marked_tile_t *remove_marked_tile(marked_tile_t *tile, int tile_nb)
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

marked_tile_t *mark_tile(pos_t pos, enum cards card)
{
    marked_tile_t *new_tile = malloc(sizeof(marked_tile_t));

    new_tile->pos = pos;
    new_tile->cards[0] = card;
    new_tile->cards_nb = 1;
    new_tile->next = NULL;

    return new_tile;
}

void add_marked_tile(marked_tile_t *tile, pos_t pos, enum cards card)
{
    marked_tile_t *new_tile = mark_tile(pos, card);

    for (; tile->next; tile = tile->next);
    tile->next = new_tile;
}

void add_cardinal(marked_tile_t *tile, pos_t pos, enum cards card)
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

int mark_tiles_around(char **map, marked_tile_t *tile, int tile_nb, pos_t size)
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