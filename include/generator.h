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

static const pos_t CARDS_POS[4] = {{0, -1}, {0, 1}, {1, 0}, {-1, 0}};


/* --- generator.c --- */
char **generator(pos_t size);

/* --- maze_printer.c --- */
void print_maze(char **map, pos_t size);

/* --- map_modifier.c --- */
char **create_map(pos_t size);
char **add_new_way(char **map, marked_tile_t *tile, int tile_nb);

/* --- mark_handler.c --- */
marked_tile_t * remove_marked_tile(marked_tile_t *tile, int tile_nb);
marked_tile_t * mark_tile(pos_t pos, enum cards card);
void            add_marked_tile(marked_tile_t *tile, pos_t pos, enum cards card);
void            add_cardinal(marked_tile_t *tile, pos_t pos, enum cards card);
int             mark_tiles_around(char **map, marked_tile_t *tile, int tile_nb, pos_t size);



#endif /* --- PRIMS_GENERATOR --- */