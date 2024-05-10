/// @brief This is a module that intitialises com port 0 to communicate with computer
/// to display all the aplication layer calls being made for debugging.
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>

void debug_init();
void debug_print(const char *message);
void debug_print_w_prefix(const char *message, const char *prefix);
void debug_print_w_uint_16(const char *message, const uint16_t *integer);
void debug_print_w_int(const char *message, const int *integer);