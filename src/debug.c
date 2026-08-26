#include <stdio.h>

#include "constants.h"
#include "debug.h"

void debug_print_game_data(struct game *game) {
    size_t i;
    size_t j;

    printf("\n");
    printf("Player name: %s\n", game->player.name);
    printf("Introductory text: %s", game->introductory_text);
    printf("\n");
    printf("[ROOMS]\n");
    printf("\n");

    for (i = 0; i < FILE_MAX_ROOMS; ++i) {
        if (game->rooms[i].room_number == 0) {
            break;
        }

        printf("Room number: %zu\n", game->rooms[i].room_number);
        printf("Room message: %s\n", game->rooms[i].message);
        printf("North connection: %zu\n", game->rooms[i].connections[NORTH]);
        printf("East connection: %zu\n", game->rooms[i].connections[EAST]);
        printf("South connection: %zu\n", game->rooms[i].connections[SOUTH]);
        printf("West connection: %zu\n", game->rooms[i].connections[WEST]);
        printf("\n");

        for (j = 0; j < FILE_MAX_CHALLENGES_PER_ROOM; j++) {
            printf("Challenge %zu: %u\n", j + 1, game->rooms[i].challenges[j]);
        }

        printf("\n");
    }
}
