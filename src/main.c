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

    load_game_from_config_file(&game);
    print_help_text();
    printf("Type 'help' to bring up these instructions (after giving your name).\n\n");

    while (user_input[0] == '\0') {
        printf("What is your name? ");
        util_wait_for_user_input(user_input);
        util_sanitise_input(user_input);
        user_input[0] = (char)toupper((int)user_input[0]);
    }

    sprintf(game.player.name, "%s", user_input);
    game.player.room = game.rooms[0];

    printf("\n%s\n\n", game.introductory_text);

    while (1) {
        printf("What would you like to do? ");
        util_wait_for_user_input(user_input);
        util_sanitise_input(user_input);
        play(&game, user_input);

#ifdef DEBUG
        print_debug_info(&game);
#endif
    }

    return EXIT_SUCCESS;
}
