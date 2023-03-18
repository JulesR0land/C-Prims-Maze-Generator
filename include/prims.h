#include <stdbool.h>

#ifndef PRIMS
#define PRIMS

// - STRUCTS - //
typedef struct coord_s coord_t;
typedef struct marked_tile_s marked_tile_t;

struct coord_s {
    int x;
    int y;
};

struct marked_tile_s {
    coord_t pos;
    int cards[4];
    int cards_nb;
    marked_tile_t *next;
};

struct arguments
{
    coord_t size;
    coord_t start;
    coord_t finish;
};


enum cards {NORTH, SOUTH, EAST, WEST};

static const coord_t CARDS_POS[4] = {{0, -1}, {0, 1}, {1, 0}, {-1, 0}};


/* --- args_handler.c --- */
void args_handler(int ac, char **av, struct arguments *arguments);

/* --- generator.c --- */
char **generator(coord_t size, coord_t start, coord_t finish);

/* --- maze_printer.c --- */
void print_maze(char **map, coord_t size);

/* --- map_modifier.c --- */
char **create_map(coord_t size);
void add_start_finish(char **map, coord_t start, coord_t finish);
void free_map(char **map, int height);
char **add_new_way(char **map, marked_tile_t *tile, int tile_nb);

/* --- mark_handler.c --- */
marked_tile_t * remove_marked_tile(marked_tile_t *tile, int tile_nb);
marked_tile_t * mark_tile(coord_t pos, enum cards card);
void            add_marked_tile(marked_tile_t *tile, coord_t pos, enum cards card);
void            add_cardinal(marked_tile_t *tile, coord_t pos, enum cards card);
int             mark_tiles_around(char **map, marked_tile_t *tile, int tile_nb, coord_t size);


#endif /* --- PRIMS --- */