#ifndef GAME_H
#define GAME_H

void game_print_help_text(void);
void game_get_name(struct game *game, char *user_input);
void game_loop(struct game *game, char *user_input);

#endif
