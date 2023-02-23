#include <stdio.h>

#include "options.h"
#include "generator.h"

int main(int ac, char **av)
{
    struct arguments args;
    char **map = NULL;

    args_handler(ac, av, &args);
    map = generator((pos_t){args.height, args.width});
    print_maze(map, (pos_t){args.height, args.width});

    return 0;
}