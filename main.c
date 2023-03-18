#include <stddef.h>

#include "prims.h"

int main(int ac, char **av)
{
    struct arguments args;
    char **map = NULL;

    args_handler(ac, av, &args);
    map = generator(args.size, args.start, args.finish);
    print_maze(map, args.size);
    free_map(map, args.size.y);

    return 0;
}