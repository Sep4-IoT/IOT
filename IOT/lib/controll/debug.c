#include "debug.h"
#include "pc_comm.h"


// rewrite for functions to use better debugs with different inputs

void debug_init(){
    pc_comm_init(9600,NULL);    // Telling the messenger how often he'll have to travel
    debug_print("Debug printing initialised \n");
}
void debug_print(char *message){ 
    uart_send_string_blocking(USART_0, message); // Just the messenger
}

void debug_print_w_prefix( char *message,  char *prefix)
{
    char debug_message[100];
    sprintf(debug_message, "%s: %s \n", prefix, message);
    debug_print(debug_message);
}

void debug_print_w_uint_16( char *message,  uint16_t *integer){
    char debug_message[100];
    sprintf(debug_message, "%s: %hu \n", message, *integer);
    debug_print(debug_message);
}
void debug_print_w_uint_8( char *message,  uint8_t *integer){
    char debug_message[100];
    sprintf(debug_message, "%s: %hu \n", message, *integer);
    debug_print(debug_message);
}

void debug_print_w_int( char *message,  int *integer){
    char debug_message[100];
    sprintf(debug_message, "%s: %d \n", message, *integer);
    debug_print(debug_message);
}

