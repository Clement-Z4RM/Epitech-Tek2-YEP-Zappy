/*
** EPITECH PROJECT, 2024
** Zappy-Server
** File description:
** options.h
*/

#ifndef ZAPPY_SERVER_OPTIONS_H_
    #define ZAPPY_SERVER_OPTIONS_H_

    #include <sys/types.h>
    #include <sys/queue.h>
    #include <stdbool.h>
    #include <stddef.h>

    /**
     * @brief Options string for getopt
     *
     * @details The ':' mean the option requires an argument
     * @details All other characters are possible options
     * ('h' is for help and will takes over all the others options)
     *
     * @warning All characters in this string must be in OPTION_PARSERS
     */
    #define OPTIONS_STRING "hp:x:y:n:c:f:"

    /**
     * @brief Macro for get next option using getopt
     */
    #define NEXT_OPT(argc, argv) getopt(argc, argv, OPTIONS_STRING)

/**
 * @brief Frequency type (simply an unsigned long)
 */
typedef ulong freq_t;

/**
 * @brief Team name entry
 */
typedef struct team_name_s {
    const char *name;
    SLIST_ENTRY(team_name_s) next;
} team_name_t;

/**
 * @brief Team names list
 */
SLIST_HEAD(team_names_s, team_name_s);
typedef struct team_names_s team_names_t;

/**
 * @brief Program options structure
 */
typedef struct options_s {
    /** @brief The usage flag (-h). Takes over all other options */
    bool usage;
    /** @brief The port number of the server */
    ushort port;
    /** @brief The world size */
    struct {
        /** @brief The width of the world */
        size_t x;
        /** @brief The height of the world */
        size_t y;
    } world;
    /** @brief  The team names. It's a linked list because we don't know
     * the number of teams when options are parsed */
    team_names_t teams;
    /** @brief The number of teams */
    u_int64_t team_count;
    /** @brief The number of authorized clients per team */
    ulong clients;
    /** @brief The frequency,
     * the reciprocal of time unit for execution of actions */
    freq_t freq;

    /** @brief Structure destructor */
    void (*destroy)(struct options_s *options);
} options_t;

extern options_t *parse_options(int argc, char *argv[]);

extern bool usage(options_t *options);

//region Option parsers
/**
 * @brief Option parser structure
 */
typedef struct option_parser_s {
    /** @brief The option name */
    const char *name;

    /** @brief True if the option requires an argument, false otherwise */
    bool argument_required;

    /**
     * @brief Option parser function
     *
     * @param options The options structure to fill
     * @param argv The arguments vector
     *
     * @return true if the option was successfully parsed, false otherwise
     */
    bool (*parser)(options_t *options, char *argv[]);
} option_parser_t;

extern bool parse_unknown(options_t *options, char *argv[]);

extern bool parse_usage(options_t *options, char *argv[]);

extern bool parse_port(options_t *options, char *argv[]);

extern bool parse_world_width(options_t *options, char *argv[]);

extern bool parse_world_height(options_t *options, char *argv[]);

extern bool parse_teams(options_t *options, char *argv[]);

extern bool parse_clients(options_t *options, char *argv[]);

extern bool parse_frequency(options_t *options, char *argv[]);

/**
 * @brief Option parsers list. Indexes are option characters
 */
static const option_parser_t OPTION_PARSERS[] = {
    ['?'] = {NULL, false, parse_unknown},
    ['h'] = {NULL, false, parse_usage},
    ['p'] = {"port", true, parse_port},
    ['x'] = {"world width", true, parse_world_width},
    ['y'] = {"world height", true, parse_world_height},
    ['n'] = {"team names", true, parse_teams},
    ['c'] = {"clients number", true, parse_clients},
    ['f'] = {"frequency", false, parse_frequency}
};
//endregion

/**
 * @brief Option validator structure (for validate_options)
 */
typedef struct option_validator_s {
    /** @brief The option parser */
    const option_parser_t *parser;

    /** @brief The option argument from options_t
     * (will be 0 if invalid, so false) */
    bool valid;
} option_validator_t;

#endif /* !ZAPPY_SERVER_OPTIONS_H_ */
