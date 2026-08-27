#ifndef UTIL_H
#define UTIL_H

void util_sanitise_input(char *user_input);
void util_leave(void);
void util_get_user_input(char *user_input);
void util_trim_start(char* text, size_t characters);
size_t util_string_to_size_t(char* text);
char util_char_uppercase(char character);

#endif
