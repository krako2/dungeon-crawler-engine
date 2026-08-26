#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "constants.h"
#include "util.h"
#include "game.h"
#include "file.h"
#include "debug.h"

int main(void) {
    static struct game game = {0};
    char user_input[GAME_MAX_RESPONSE_LENGTH] = {'\0'};

    file_load_config(&game);
    game_print_help_text();
    printf("Type 'help' to bring up these instructions (after giving your name).\n\n");

    game_ask_for_name(user_input);

    sprintf(game.player.name, "%s", user_input);
    game.player.room = game.rooms[0];

    printf("\n%s\n\n", game.introductory_text);

    game_start(&game, user_input);
}
