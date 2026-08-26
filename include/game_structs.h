#ifndef GAME_STRUCTS_H
#define GAME_STRUCTS_H

#include <stddef.h>

#include "file_defines.h"
#include "game_defines.h"
#include "enums.h"

struct room {
    char message[FILE_MAX_ROOM_MESSAGE_LENGTH];
    enum challenge challenges[FILE_MAX_CHALLENGES_PER_ROOM];
    size_t connections[4]; /* North, East, South, West */
    size_t room_number;
};

struct player {
    struct room room;
    char name[GAME_MAX_RESPONSE_LENGTH];
};

struct game {
    struct player player;
    struct room rooms[FILE_MAX_ROOMS];
    char introductory_text[FILE_INTRO_TEXT_MAX_LENGTH];
};

#endif
