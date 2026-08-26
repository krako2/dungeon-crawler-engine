#ifndef GAME_H
#define GAME_H

void game_print_help_text(void);
void game_ask_for_name(char *user_input);
void game_start(struct game *game, char *user_input);

#endif
