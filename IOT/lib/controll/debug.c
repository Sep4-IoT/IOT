#include "debug.h"
#include "pc_comm.h"

// rewrite for functions to use better debugs with different inputs

void debug_init(){
    pc_comm_init(9600,NULL);    // Telling the messenger how often he'll have to travel
    debug_print("Debug printing initialised \n");
}
void debug_print(const char *message){ 
    uart_send_string_blocking(USART_0, message); // Just the messenger
}

void debug_print_w_prefix(const char *message, const char *prefix)
{
    char debug_message[100];
    sprintf(debug_message, "%s: %s", prefix, message);
    debug_print(debug_message);
}