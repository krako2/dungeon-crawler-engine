#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "shared.h"
#include "challenge.h"

#include "string.h"
#include "io.h"

static void challenge_clear(struct game *game) {
    size_t i;
    size_t j;

    for (i = 0; i < MAX_ROOMS; ++i) {
        if (game->player.current_room.room_number != game->rooms[i].room_number) {
            continue;
        }
    
        for (j = 0; j < MAX_CHALLENGES_PER_ROOM; ++j) {
            if (game->rooms[i].challenges[j] != NONE) {
                game->rooms[i].challenges[j] = NONE;
                game->player.current_room.challenges[j] = NONE;
                break;
            }
        }
    
        break;
    }

    if (i == MAX_ROOMS) {
        printf("Cannot clear challenge from a room.\n");
        io_leave();
    }
}

void challenge_physical(struct game *game) {
    struct challenge_physical delinquent;
    char user_input[MAX_RESPONSE_LENGTH] = {'\0'};

    delinquent.health = 2;

    printf("A delinquent appears! They look at you menacingly.\n");

    while (delinquent.health > 0) {
        printf("How do you respond? ");

        io_get_user_input(user_input);

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

    challenge_clear(game);
}

void challenge_puzzle(struct game *game) {
    char user_input[MAX_RESPONSE_LENGTH] = {'\0'};
    struct challenge_puzzle puzzle;
    size_t answer;

    srand((unsigned)time(NULL));

    puzzle.first = (unsigned)rand() % 100u + 1u;
    puzzle.second = (unsigned)rand() % 100u + 1u;
    answer = puzzle.first * puzzle.second;

    printf("There is a note on the floor. You pick it up.\n");
    printf("It says, '%u x %u'.\n", puzzle.first, puzzle.second);

    while (string_to_size_t(user_input) != answer) {
        printf("What could it possibly mean? ");
        io_get_user_input(user_input);
    }

    printf("\nYou write '%s' on the note. Nice.\n", user_input);

    challenge_clear(game);
}
