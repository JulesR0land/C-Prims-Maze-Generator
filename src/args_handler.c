#include <argp.h>
#include <time.h>
#include <stdlib.h>

#include "prims.h"

// - CONSTANTS - //
#define DEFAULT_SIZE    (coord_t){7, 7};
#define DEFAULT_START   (coord_t){-1, -1};
#define DEFAULT_FINISH  (coord_t){-1, -1};

static coord_t get_coord(char *arg)
{
    coord_t coord = {-1, -1};

    if (!arg)
        return coord;

    coord.x = atoi(arg);
    if (coord.x < 0 || arg[0] < '0' || arg[0] > '9') {
        coord.x = -1;
        return coord;
    }

    for (; *arg >= '0' && *arg <= '9'; arg++);
    for (; *arg < '0' || *arg > '9'; arg++)
        if (*arg == '\0') {
            coord.x = -1;
            return coord;
        }

    coord.y = atoi(arg);
    if (coord.y < 0) {
        coord.y = -1;
        return coord;
    }

    for (; *arg != '\0'; arg++)
        if (*arg < '0' || *arg > '9') {
            coord.x = -1;
            return coord;
        }
    return coord;
}

static error_t parse_opt(int key, char *arg, struct argp_state *state)
{
    struct arguments *arguments = state->input;

    switch(key) {
        case 'h':
            arguments->size.y = atoi(arg);
            if (arguments->size.y < 3)
                argp_usage(state);
            break;
        case 'w':
            arguments->size.x = atoi(arg);
            if (arguments->size.x < 3)
                argp_usage(state);
            break;
        case 's':
            arguments->start = get_coord(arg);
            if (arguments->start.x < 0)
                argp_usage(state);
            break;
        case 'f':
            arguments->finish = get_coord(arg);
            if (arguments->finish.x < 0)
                argp_usage(state);
            break;
        case ARGP_KEY_ARG:
            argp_usage(state);
            break;
        case ARGP_KEY_END:
            break;
        default:
            return ARGP_ERR_UNKNOWN;
    }

    return 0;
}

static void setup_default(struct arguments *arguments)
{
    arguments->size = DEFAULT_SIZE;
    arguments->start = DEFAULT_START;
    arguments->finish = DEFAULT_FINISH;
}

static void check_start_point(struct arguments *args)
{
    if (args->start.x < 0 || args->start.x >= args->size.x ||
        args->start.y < 0 || args->start.y >= args->size.y) {
        args->start.x = rand() % args->size.x;
        args->start.y = rand() % args->size.y;
    }
}

static void check_finish_point(struct arguments *args)
{
    if (args->finish.x < 0 || args->finish.x >= args->size.x ||
        args->finish.y < 0 || args->finish.y >= args->size.y) {
        args->finish.x = rand() % args->size.x;
        args->finish.y = rand() % args->size.y;
    }

    while (args->start.x == args->finish.x && args->start.y == args->finish.y) {
        args->finish.x = rand() % args->size.x;
        args->finish.y = rand() % args->size.y;
    }
}

void args_handler(int ac, char **av, struct arguments *arguments)
{
    char *args_doc = "";
    char *program_doc = "";
    struct argp_option options[5] = {
        {"height", 'h', "height", 0, "Set height of the maze (min: 3, default: 7)", 0},
        {"width", 'w', "width", 0, "Set width of the maze (min: 3, default: 7)", 0},
        {"start", 's', "\"X Y\"", 0, "Set the start point of the maze (default is random)", 0},
        {"finish", 'f', "\"X Y\"", 0, "Set the finish point of the maze (default is random and set at random if the same as start)", 0},
        {0}
    };

    struct argp argp = {
        options,
        parse_opt,
        args_doc,
        program_doc,
        NULL, NULL, NULL
    };

    setup_default(arguments);
    argp_parse(&argp, ac, av, 0, 0, arguments);
    check_start_point(arguments);
    check_finish_point(arguments);
}