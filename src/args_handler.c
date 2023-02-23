#include <argp.h>
#include <stdlib.h>

#include "options.h"

static error_t parse_opt(int key, char *arg, struct argp_state *state){
    struct arguments *arguments = state->input;

    switch(key) {
        case 'h':
            arguments->height = atoi(arg);
            if (arguments->height < 3)
                argp_usage(state);
            break;
        case 'w':
            arguments->width = atoi(arg);
            if (arguments->width < 3)
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
    arguments->height = DEFAULT_HEIGHT;
    arguments->width = DEFAULT_WIDTH;
}

void args_handler(int ac, char **av, struct arguments *arguments)
{
    struct argp_option options[3] = {
        {"height", 'h', "maze-height", 0, "Set height of the maze (min: 3, default: 7)", 0},
        {"width", 'w', "maze-width", 0, "Set width of the maze (min: 3, default: 7)", 0},
        {0}
    };

    struct argp argp = {
        options,
        parse_opt,
        ARGS_DOC,
        PROGRAM_DOC,
        NULL, NULL, NULL
    };

    setup_default(arguments);
    argp_parse(&argp, ac, av, 0, 0, arguments);
}