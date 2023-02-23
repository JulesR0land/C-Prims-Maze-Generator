#include <stdbool.h>

#ifndef PRIMS_GENERATOR
#define PRIMS_GENERATOR

enum cards {NORTH, SOUTH, EAST, WEST};

typedef struct marked_tile_s marked_tile_t;
typedef struct pos_s pos_t;

struct pos_s {
    int x;
    int y;
};

struct marked_tile_s {
    pos_t pos;
    int cards[4];
    int cards_nb;
    marked_tile_t *next;
};


/* --- generator.c --- */
char **generator(pos_t size);

/* --- maze_printer.c --- */
void print_maze(char **map, pos_t size);

#endif /* --- PRIMS_GENERATOR --- */