#ifndef CONSTANT_H
#define CONSTANT_H

#define MAX_RESPONSE_LENGTH 16
#define MAX_ROOMS 64
#define MAX_ROOM_MESSAGE_LENGTH 200
#define MAX_CHALLENGES_PER_ROOM 8
#define INTRO_TEXT_MAX_LENGTH 80
#define MAX_FILE_LINE_LENGTH 203
#define CONFIG_FILE_NAME "config.txt"

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
    char message[MAX_ROOM_MESSAGE_LENGTH];
    enum challenge challenges[MAX_CHALLENGES_PER_ROOM];
    size_t connections[4]; /* North, East, South, West */
    size_t room_number;
};

struct player {
    struct room room;
    char name[MAX_RESPONSE_LENGTH];
};

#endif
