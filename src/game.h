#ifndef GAME_H
#define GAME_H

struct game {
    struct player player;
    struct room rooms[MAX_ROOMS];
    char introductory_text[INTRO_TEXT_MAX_LENGTH];
};

void print_help_text(void);
void play(struct game *game, char *user_input);

#endif
