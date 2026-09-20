#include <stdio.h>

#include "io.h"

#include "player.h"
#include "string.h"

void player_get_name(char *name_output) {
    while (name_output[0] == '\0') {
        printf("What is your name? ");
        io_get_user_input(name_output);
        name_output[0] = string_char_uppercase(name_output[0]);
    }
}
