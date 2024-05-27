/// @brief This is a module that intitialises com port 0 to communicate with computer
/// to display all the aplication layer calls being made for debugging.
#pragma once
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>

void debug_init();
void debug_print( char *message);
void debug_print_w_prefix( char *message,  char *prefix);
void debug_print_w_uint_16( char *message,  uint16_t *integer);
void debug_print_w_uint_8( char *message,  uint8_t *integer);
void debug_print_w_int( char *message,  int *integer);