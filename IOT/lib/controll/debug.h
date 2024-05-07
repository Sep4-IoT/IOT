/// @brief This is a module that intitialises com port 0 to communicate with computer
/// to display all the aplication layer calls being made for debugging.
#include <stdbool.h>

void debug_init();
void debug_print(const char *message);
void debug_print_w_prefix(const char *message, const char *prefix);