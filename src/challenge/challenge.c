#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "game_structs.h"
#include "util.h"
#include "challenge.h"

struct challenge_physical {
    int health;
};

struct challenge_puzzle {
    unsigned first;
    unsigned second;
};

void challenge_physical(void) {
    struct challenge_physical delinquent;
    char user_input[GAME_MAX_RESPONSE_LENGTH] = {'\0'};

    delinquent.health = 2;

    printf("A delinquent appears! They look at you menacingly.\n");

    while (delinquent.health > 0) {
        printf("How do you respond? ");

        util_get_user_input(user_input);
        util_sanitise_input(user_input);

        if (strncmp(user_input, "attack", 6) != 0) {
            continue;
        }
        
        delinquent.health--;
        if (delinquent.health > 0) {
            printf("\nThe delinquent takes a hit.\n");
        } else {
            printf("\nThe delinquent falls and dies.\n");
        }
    }
}

void challenge_puzzle(void) {
    char user_input[GAME_MAX_RESPONSE_LENGTH] = {'\0'};
    struct challenge_puzzle puzzle;
    size_t answer;

    srand((unsigned) time(NULL));

    puzzle.first = (unsigned) rand() % 100u + 1u;
    puzzle.second = (unsigned) rand() % 100u + 1u;
    answer = puzzle.first * puzzle.second;

    printf("There is a note on the floor. You pick it up.\n");
    printf("It says, '%u x %u'.\n", puzzle.first, puzzle.second);

    while (util_string_to_size_t(user_input) != answer) {
        printf("What could it possibly mean? ");
        util_get_user_input(user_input);
        util_sanitise_input(user_input);
    }

    printf("\nYou write '%s' on the note. Nice.\n", user_input);
}

void challenge_clear(struct game *game) {
    size_t i;
    size_t j;

    for (i = 0; i < FILE_MAX_ROOMS; ++i) {
        if (game->player.room.room_number != game->rooms[i].room_number) {
            continue;
        }
    
        for (j = 0; j < FILE_MAX_CHALLENGES_PER_ROOM; ++j) {
            if (game->rooms[i].challenges[j] != NONE) {
                game->rooms[i].challenges[j] = NONE;
                game->player.room.challenges[j] = NONE;
                break;
            }
        }
    
        break;
    }

    if (i == FILE_MAX_ROOMS) {
        printf("Cannot clear challenge from a room.\n");
        util_leave();
    }
}
