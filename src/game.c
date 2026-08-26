#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>

#include "constants.h"
#include "util.h"
#include "game.h"
#include "challenge.h"
#include "debug.h"

static void game_move_player(struct game *game, enum direction direction) {
    size_t i;
    size_t next_room = game->player.room.connections[direction];

    if (next_room == 0) {
        printf("\nYou hit a wall. Ouch!\n");
        return;
    }
    
    for (i = 0; i < FILE_MAX_ROOMS; ++i) {
        if (game->rooms[i].room_number == next_room) {
            game->player.room = game->rooms[i];
            break;
        }
    }

    if (i == FILE_MAX_ROOMS) {
        printf("Couldn't find room.\n");
        util_leave();
    }

    printf("\n%s", game->player.room.message);
}

static void game_play(struct game *game, char *user_input) {
    size_t i;

    if (strncmp(user_input, "help", 4) == 0) {
        printf("\n");
        game_print_help_text();
        return;
    } else if (strncmp(user_input, "north", 5) == 0) {
        game_move_player(game, NORTH);
    } else if (strncmp(user_input, "east", 4) == 0) {
        game_move_player(game, EAST);
    } else if (strncmp(user_input, "south", 5) == 0) {
        game_move_player(game, SOUTH);
    } else if (strncmp(user_input, "west", 4) == 0) {
        game_move_player(game, WEST);
    } else if (strncmp(user_input, "exit", 4) == 0 ||
               strncmp(user_input, "leave", 5) == 0 ||
               strncmp(user_input, "quit", 4) == 0 ||
               strncmp(user_input, "out", 3) == 0) {
        util_leave();
    }

    if (game->player.room.room_number == 1) {
        printf("Congratulations, %s!\n", game->player.name);
        util_leave();
    }

    for (i = 0; i < FILE_MAX_CHALLENGES_PER_ROOM; ++i) {
        switch (game->player.room.challenges[i]) {
        case NONE:
            break;
        case PHYSICAL:
            challenge_physical();
            challenge_clear(game);
            break;
        case PUZZLE:
            challenge_puzzle();
            challenge_clear(game);
            break;
        default:
            break;
        }
    }
}

void game_print_help_text(void) {
    const char *help_text =
    "Type compass directions to game_move_player.\n"
    "Type 'attack' to attack.\n"
    "Type numbers to solve puzzles.\n"
    "Type 'exit', 'leave' or similar to quit.\n";

    printf("%s", help_text);
}

void game_ask_for_name(char *user_input) {
    while (user_input[0] == '\0') {
        printf("What is your name? ");
        util_get_user_input(user_input);
        util_sanitise_input(user_input);
        user_input[0] = (char)toupper((int)user_input[0]);
    }
}

void game_start(struct game *game, char *user_input) {
    while (1) {
        printf("What would you like to do? ");
        util_get_user_input(user_input);
        util_sanitise_input(user_input);
        game_play(game, user_input);

#ifdef DEBUG
        debug_print_game_data(game);
#endif
    }
}
