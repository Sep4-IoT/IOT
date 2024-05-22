#include "debug.h"
#include "pc_comm.h"


// rewrite for functions to use better debugs with different inputs

void debug_init(){
    pc_comm_init(9600,NULL);    // Telling the messenger how often he'll have to travel
    debug_print("Debug printing initialised \n");
}
void debug_print(const char *message) {
    char debug_message_with_newline[256]; // Assuming the message is not longer than 255 characters
    snprintf(debug_message_with_newline, sizeof(debug_message_with_newline), "%s\n", message);
    uart_send_string_blocking(USART_0, debug_message_with_newline);
}

void debug_print_w_prefix(const char *message, const char *prefix)
{
    char debug_message[100];
    sprintf(debug_message, "%s: %s \n", prefix, message);
    debug_print(debug_message);
}

void debug_print_w_uint_16(const char *message, const uint16_t *integer){
    char debug_message[100];
    sprintf(debug_message, "%s: %hu \n", message, *integer);
    debug_print(debug_message);
}
void debug_print_w_uint_8(const char *message, const uint8_t *integer){
    char debug_message[100];
    sprintf(debug_message, "%s: %hu \n", message, *integer);
    debug_print(debug_message);
}

void debug_print_w_int(const char *message, const int *integer){
    char debug_message[100];
    sprintf(debug_message, "%s: %d \n", message, *integer);
    debug_print(debug_message);
}