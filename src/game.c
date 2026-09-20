#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "shared.h"
#include "game.h"

#include "string.h"
#include "challenge.h"
#include "file.h"
#include "player.h"
#include "io.h"

static void print_help_text(void) {
    const char *help_text =
    "Type compass directions to move.\n"
    "Type 'attack' to attack.\n"
    "Type numbers to solve puzzles.\n"
    "Type 'exit', 'leave' or similar to quit.\n";

    printf("%s", help_text);
}

static void load_game(struct game *game) {
    file_load_config(game);
    game->player.current_room = game->rooms[0];
}

static void print_initial_instructions(void) {
    print_help_text();
    printf("Type 'help' to bring up these instructions (after giving your name).\n\n");
}

static void print_introductory_text(char *introductory_text) {
    printf("\n%s\n\n", introductory_text);
}

static void print_main_loop_message(void) {
    printf("What would you like to do? ");
}

static void move_player(struct game *game, enum direction direction) {
    size_t i;
    unsigned next_room = game->player.current_room.connections[direction];

    if (next_room == 0) {
        printf("\nYou hit a wall. Ouch!\n");
        return;
    }
    
    for (i = 0; i < MAX_ROOMS; ++i) {
        if (game->rooms[i].room_number == next_room) {
            game->player.current_room = game->rooms[i];
            break;
        }
    }

    if (i == MAX_ROOMS) {
        printf("Couldn't find room.\n");
        io_leave();
    }

    printf("\n%s", game->player.current_room.message);
}

static void help_check(char *user_input) {
    if (strncmp(user_input, "help", 4) == 0) {
        printf("\n");
        print_help_text();
        return;
    }
}

static void move_check(struct game *game) {
    if (strncmp(game->user_input, "north", 5) == 0) {
        move_player(game, NORTH);
    } else if (strncmp(game->user_input, "east", 4) == 0) {
        move_player(game, EAST);
    } else if (strncmp(game->user_input, "south", 5) == 0) {
        move_player(game, SOUTH);
    } else if (strncmp(game->user_input, "west", 4) == 0) {
        move_player(game, WEST);
    }
}

static void exit_check(char *user_input) {
    if (strncmp(user_input, "exit", 4) == 0 ||
            strncmp(user_input, "leave", 5) == 0 ||
            strncmp(user_input, "quit", 4) == 0 ||
            strncmp(user_input, "out", 3) == 0) {
        io_leave();
    }
}

static void finish_check(unsigned room_number, char *player_name) {
    if (room_number == 1) {
        printf("Congratulations, %s!\n", player_name);
        io_leave();
    }
}

static void play_challenges(struct game *game) {
    size_t i;
    for (i = 0; i < MAX_CHALLENGES_PER_ROOM; ++i) {
        switch (game->player.current_room.challenges[i]) {
        case NONE:
            break;
        case PHYSICAL:
            challenge_physical(game);
            break;
        case PUZZLE:
            challenge_puzzle(game);
            break;
        default:
            break;
        }
    }
}

static void play(struct game *game) {
    help_check(game->user_input);
    move_check(game);
    exit_check(game->user_input);
    finish_check(game->player.current_room.room_number, game->player.name);
    play_challenges(game);
}

static void main_loop(struct game *game) {
    while (1) {
        print_main_loop_message();
        io_get_user_input(game->user_input);
        play(game);

        #ifdef DEBUG
        debug_print_all_game_data(game);
        #endif
    }
}

void game_start(void) {
    static struct game game = {0};

    load_game(&game);
    print_initial_instructions();
    player_get_name(game.player.name);
    print_introductory_text(game.introductory_text);

    main_loop(&game);
}
