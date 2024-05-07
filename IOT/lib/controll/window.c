#include "window.h"
#include "debug.h"



uint8_t windowAngle;
extern bool window_debugMode;

void window_open(){
    // Opens servo, no questions asked
    servo_set_angle(180);
    windowAngle = 180;
    if(window_debugMode){debug_print("window close \n");}
}
void window_close(){
    // Closes servo, no questions asked
    servo_set_angle(0);
    windowAngle = 0;
    if(window_debugMode){debug_print("window close \n");}
}
void window_open_at_angle(uint8_t angle){
    // Sets to an angle of openess, one question asked
    servo_set_angle(angle);
    windowAngle = angle;
    if (window_debugMode) {
        char debugMessage[50];
        sprintf(debugMessage, "window openAtAngle: %u  \n", windowAngle);
        debug_print(debugMessage);
    }
}

int window_get_state(){
    // Reminds you of your window status
    if (window_debugMode) {
        char debugMessage[50];
        sprintf(debugMessage, "window getState:  %u \n", windowAngle);
        debug_print(debugMessage);
    }
    return windowAngle;
}