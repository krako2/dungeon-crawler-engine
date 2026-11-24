#ifndef LANGUAGE_H
#define LANGUAGE_H

#include "shared.h"

void language_ask_for_language(struct game *game);
const char *language_main_loop_prompt(enum language language);

#endif
