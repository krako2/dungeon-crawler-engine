#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>

#include "constants.h"
#include "util.h"
#include "file.h"

struct parse_data {
    size_t room_counter;
    size_t room_challenge_counter;
    size_t line_counter;
    size_t line_character_counter;
    int is_reading_introductory_text;
    char line[FILE_MAX_FILE_LINE_LENGTH];
    char current_character;
};

static void write_template_config_file(FILE *config_file) {
    const char *template =
    "[ROOMS]\n"
    "\n"
    "ROOM NUMBER: 100\n"
    "MESSAGE: You enter a dark room. A light glimmers up north.\n"
    "CONNECTIONS:\n"
    "\tNORTH: 1\n"
    "\tEAST: None\n"
    "\tSOUTH: None\n"
    "\tWEST: None\n"
    "CHALLENGE: Physical, Puzzle\n"
    "\n"
    "ROOM NUMBER: 1\n"
    "MESSAGE: You enter the winning room.\n"
    "CONNECTIONS:\n"
    "\tNORTH: None\n"
    "\tEAST: None\n"
    "\tSOUTH: None\n"
    "\tWEST: None\n"
    "CHALLENGE: None\n"
    "\n"
    "[INTRODUCTORY TEXT]\n"
    "\n"
    "You arise from a deep rest. There's a door up north.\n";

    fputs(template, config_file);
}

static void parse_introductory_text(struct parse_data *parse_data, struct game *game) {
    static size_t i = 0;
    if (i == INT_MAX) {
        puts("Error: Introductory text is too long.");
        util_leave();
    }
    while (parse_data->line[i] != '\n') {
        game->introductory_text[i] = parse_data->line[i];
        ++i;

        if (i == INT_MAX) {
            puts("Error: Introductory text is too long.");
            util_leave();
        }
    }
}

static void parse_challenges_into_room(struct parse_data *parse_data, struct game *game) {
    while (parse_data->line[0] != '\n') {
        if (strncmp(parse_data->line, "None", 4) == 0) {
            util_trim_start(parse_data->line, 4);
        } else if (strncmp(parse_data->line, "Physical", 8) == 0) {
            util_trim_start(parse_data->line, 8);
            game->rooms[parse_data->room_counter].challenges[parse_data->room_challenge_counter] = PHYSICAL;
            parse_data->room_challenge_counter++;
        } else if (strncmp(parse_data->line, "Puzzle", 6) == 0) {
            util_trim_start(parse_data->line, 6);
            game->rooms[parse_data->room_counter].challenges[parse_data->room_challenge_counter] = PUZZLE;
            parse_data->room_challenge_counter++;
        } else if (strncmp(parse_data->line, ", ", 2) == 0) {
            util_trim_start(parse_data->line, 2);
        } else {
            break;
        }
    }

    if (parse_data->room_challenge_counter > FILE_MAX_CHALLENGES_PER_ROOM) {
        printf("Error: Too many challenges assigned to room %zu (line %zu, max %d, currently %zu).\n",
            game->rooms[parse_data->room_counter].room_number,
            parse_data->line_counter,
            FILE_MAX_CHALLENGES_PER_ROOM,
            parse_data->room_challenge_counter
        );
        util_leave();
    }

    parse_data->room_counter++;

    if (parse_data->room_counter >= FILE_MAX_ROOMS) {
        printf("Error: Too many rooms in %s (max %d).", FILE_CONFIG_FILE_NAME, FILE_MAX_ROOMS);
    }
}

static void move_to_next_line(struct parse_data *parse_data) {
    parse_data->line_counter++;
    parse_data->line_character_counter = 0;
    memset(parse_data->line, 0, FILE_MAX_FILE_LINE_LENGTH);
}

static void parse_config_file_into_game(FILE *config_file, struct game *game) {
    struct parse_data parse_data = {0};
    parse_data.line_counter = 1;

    while ((parse_data.current_character = (char) fgetc(config_file)) != EOF) {
        parse_data.line[parse_data.line_character_counter] = parse_data.current_character;
        parse_data.line_character_counter++;

        if (parse_data.line_character_counter >= FILE_MAX_FILE_LINE_LENGTH) {
            printf("Error: Line %zu of %s is too long.\n", parse_data.line_counter, FILE_CONFIG_FILE_NAME);
            util_leave();
        }

        if (parse_data.current_character != '\n') {
            continue;
        }

        if (parse_data.is_reading_introductory_text) {
            parse_introductory_text(&parse_data, game);
            move_to_next_line(&parse_data);
            continue;
        }

        if (strncmp(parse_data.line, "ROOM NUMBER: ", 13) == 0) {
            util_trim_start(parse_data.line, 13);
            game->rooms[parse_data.room_counter].room_number = util_string_to_size_t(parse_data.line);
        } else if (strncmp(parse_data.line, "MESSAGE: ", 9) == 0) {
            util_trim_start(parse_data.line, 9);
            sprintf(game->rooms[parse_data.room_counter].message, "%s", parse_data.line);
        } else if (strncmp(parse_data.line, "\tNORTH: ", 8) == 0) {
            game->rooms[parse_data.room_counter].connections[NORTH] = util_string_to_size_t(parse_data.line);
        } else if (strncmp(parse_data.line, "\tEAST: ", 7) == 0) {
            game->rooms[parse_data.room_counter].connections[EAST] = util_string_to_size_t(parse_data.line);
        } else if (strncmp(parse_data.line, "\tSOUTH: ", 8) == 0) {
            game->rooms[parse_data.room_counter].connections[SOUTH] = util_string_to_size_t(parse_data.line);
        } else if (strncmp(parse_data.line, "\tWEST: ", 7) == 0) {
            game->rooms[parse_data.room_counter].connections[WEST] = util_string_to_size_t(parse_data.line);
        } else if (strncmp(parse_data.line, "CHALLENGE: ", 11) == 0) {
            util_trim_start(parse_data.line, 11);
            parse_challenges_into_room(&parse_data, game);
        } else if (strncmp(parse_data.line, "[INTRODUCTORY TEXT]", 19) == 0) {
            parse_data.is_reading_introductory_text = 1;
        }

        move_to_next_line(&parse_data);
    }
}

void load_game_from_config_file(struct game *game) {
    FILE *config_file = fopen(FILE_CONFIG_FILE_NAME, "r");

    if (config_file != NULL) {
        parse_config_file_into_game(config_file, game);
        fclose(config_file);
        return;
    }

    config_file = fopen(FILE_CONFIG_FILE_NAME, "w");

    if (config_file == NULL) {
        puts("Error: Cannot create file.");
        util_leave();
    }

    write_template_config_file(config_file);

    fclose(config_file);

    config_file = fopen(FILE_CONFIG_FILE_NAME, "r");

    if (config_file == NULL) {
        puts("Error: Cannot locate file.");
        util_leave();
    }

    rewind(config_file);
    parse_config_file_into_game(config_file, game);
    fclose(config_file);
}
