#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "shared.h"
#include "io.h"

static void sanitise_input(char *user_input) {
    size_t read = 0;
    size_t write = 0;

    while (user_input[read] != '\0') {
        if (isspace(user_input[read])) {
            ++read;
            continue;
        }

        if (user_input[read] >= 'A' && user_input[read] <= 'Z') {
            user_input[read] += 32;
        }

        user_input[write] = user_input[read];

        ++write;
        ++read;
    }

    user_input[write] = '\0';
}

void io_get_user_input(char *user_input) {
    char *newline_position;

    if (fgets(user_input, MAX_RESPONSE_LENGTH, stdin) == NULL) {
        exit(-1);
    }

    newline_position = strchr(user_input, '\n');

    if (newline_position == NULL) {
        while (getchar() != '\n');
    } else {
        *newline_position = '\0';
    }

    sanitise_input(user_input);
}

void io_leave(void) {
    char user_input[MAX_RESPONSE_LENGTH] = {'\0'};

    while (strncmp(user_input, "\n", 1) != 0) {
        char *newline_position;

        printf("Press enter to leave.\n");

        if (fgets(user_input, MAX_RESPONSE_LENGTH, stdin) == NULL) {
            exit(1);
        }

        newline_position = strchr(user_input, '\n');

        if (newline_position == NULL) {
            while(getchar() != '\n');
        }
    }

    exit(1);
}
