#ifndef CONSTANTS_H
#define CONSTANTS_H

#define FILE_MAX_ROOMS 64
#define FILE_MAX_ROOM_MESSAGE_LENGTH 200
#define FILE_MAX_CHALLENGES_PER_ROOM 8
#define FILE_INTRO_TEXT_MAX_LENGTH 80
#define FILE_MAX_FILE_LINE_LENGTH 203
#define FILE_CONFIG_FILE_NAME "config.txt"

#define GAME_MAX_RESPONSE_LENGTH 16

enum challenge {
    NONE,
    PHYSICAL,
    PUZZLE
};

enum direction {
    NORTH,
    EAST,
    SOUTH,
    WEST
};

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
