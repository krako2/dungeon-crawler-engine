#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "shared.hpp"
#include "io.hpp"

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

void io_print_introductory_text(char *introductory_text) {
    printf("\n%s\n\n", introductory_text);
}

void io_print_help_text(void) {
    const char *help_text =
    "Type compass directions to move.\n"
    "Type 'attack' to attack.\n"
    "Type numbers to solve puzzles.\n"
    "Type 'exit', 'leave' or similar to quit.\n";

    printf("%s", help_text);
}

void io_print_initial_instructions(void) {
    io_print_help_text();
    printf("Type 'help' to bring up these instructions (after giving your name).\n\n");
}

void io_print_main_loop_message(void) {
    printf("What would you like to do? ");
}
