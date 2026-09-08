#ifndef FILE_STRUCTS_H
#define FILE_STRUCTS_H

#include <stddef.h>

#include "file_macros.h"

struct parse_data {
    size_t room_counter;
    size_t room_challenge_counter;
    size_t line_counter;
    size_t line_character_counter;
    int is_reading_introductory_text;
    char line[FILE_MAX_FILE_LINE_LENGTH];
    char current_character;
};

#endif
