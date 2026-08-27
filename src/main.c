#include <stdio.h>
#include <stdlib.h>

#include "game_structs.h"
#include "game.h"
#include "file.h"

int main(void)
{
    static struct game game = {0};
    char user_input[GAME_MAX_RESPONSE_LENGTH] = {'\0'};

    file_load_config(&game);
    game_print_help_text();
    printf("Type 'help' to bring up these instructions (after giving your name).\n\n");
    game_get_name(&game, user_input);

    printf("\n%s\n\n", game.introductory_text);

    game_loop(&game, user_input);
}
