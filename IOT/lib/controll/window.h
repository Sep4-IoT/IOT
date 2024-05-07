/// @brief module is reponsible for managing the servo/window
/// Module also contains the state of the window

#include <servo.h>

void window_open();    
void window_close();
void window_open_at_angle(uint8_t angle);
int window_get_state(); // get last set state of window