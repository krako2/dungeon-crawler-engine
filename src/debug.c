#include <stdio.h>
#include "constant.h"

void print_debug_info(struct game *game) {
    printf("\n");
    printf("Player name: %s\n", game->player.name);
    printf("Introductory text: %s", game->introductory_text);
    printf("\n");
    printf("[ROOMS]\n");
    printf("\n");

    size_t i;
    for (i = 0; i < MAX_ROOMS; ++i) {
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
        
        size_t j;
        for (j = 0; j < MAX_CHALLENGES_PER_ROOM; j++) {
            printf("Challenge %zu: %u\n", j + 1, game->rooms[i].challenges[j]);
        }

        printf("\n");
    }
}
