#ifndef SHARED_H
#define SHARED_H

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

struct parse_data {
    size_t room_counter;
    size_t room_challenge_counter;
    size_t line_counter;
    size_t line_character_counter;
    int is_reading_introductory_text;
    char line[MAX_FILE_LINE_LENGTH];
    char current_character;
};

struct room {
    char message[MAX_ROOM_MESSAGE_LENGTH];
    enum challenge challenges[MAX_CHALLENGES_PER_ROOM];
    unsigned connections[4]; /* North, East, South, West */
    unsigned room_number;
};

struct player {
    struct room current_room;
    char name[MAX_RESPONSE_LENGTH];
};

struct game {
    struct player player;
    struct room rooms[MAX_ROOMS];
    char introductory_text[INTRO_TEXT_MAX_LENGTH];
    char user_input[MAX_RESPONSE_LENGTH];
};

struct challenge_physical {
    int health;
};

struct challenge_puzzle {
    unsigned first;
    unsigned second;
};

#endif
