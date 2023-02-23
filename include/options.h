#include <stdbool.h>

#ifndef MAZE_OPTIONS
#define MAZE_OPTIONS

#define PROGRAM_VERSION "C-Prims-maze-generator 1.0"
#define ARGS_DOC         ""
#define PROGRAM_DOC     "documentation for your cool application :)"

#define DEFAULT_WIDTH   7
#define DEFAULT_HEIGHT  7

enum args_errors {NO_ERROR, BAD_SIZE};

struct arguments
{
    int height;
    int width;
};


/* --- args_handler.c --- */
void args_handler(int ac, char **av, struct arguments *arguments);

#endif /* --- MAZE_OPTIONS --- */