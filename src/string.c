#include "stddef.h"

#include "shared.h"
#include "string.h"

void string_trim_start(char *text, size_t characters) {
    size_t i = 0;
    size_t j;

    while (text[i + characters] != '\0') {
        text[i] = text[i + characters];
        ++i;
    }

    for (j = 0; j < characters; ++j) {
        text[i + j] = '\0';
    }
}

size_t string_to_size_t(char *text) {
    size_t value = 0;
    size_t i = 0;

    while (text[i] != '\0') {
        if (text[i] >= '0' && text[i] <= '9') {
            value = (value * 10) + (size_t)text[i] - '0';
        }

        ++i;
    }

    return value;
}

unsigned string_to_unsigned(char *text) {
    unsigned value = 0;
    size_t i = 0;

    while (text[i] != '\0') {
        if (text[i] >= '0' && text[i] <= '9') {
            value = (value * 10) + (unsigned)text[i] - '0';
        }

        ++i;
        
    }

    return value;
}

char string_char_uppercase(char character) {
    return (character >= 97 && character <= 122) ? character - 32 : character;
}
