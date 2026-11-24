#include <stdio.h>

#include "language.h"
#include "io.h"
#include "string.h"

void language_ask_for_language(struct game* game) {
	puts("Select your language (type the number).");
	puts("1 - English");
	puts("2 - Polish");
	io_get_user_input(game->user_input);
	game->language = string_to_unsigned(game->user_input) - 1;
}

const char* language_main_loop_prompt(enum language language) {
	switch (language) {
	case POLISH:
		return "Co chcesz? ";
	default:
		return "What would you like to do? ";
	};
}
