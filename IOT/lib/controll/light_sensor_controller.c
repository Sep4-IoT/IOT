#include "light_sensor_controller.h"
#include "debug.h"
#include "light.h"

extern bool light_sensor_controller_debugMode;

void light_sensor_controller_init(){
    //Debug
    if (light_sensor_controller_debugMode)
    {
        debug_print_w_prefix("light_sensor_controller_init","called");
    }
    //EndOfDebug

    light_init();

    //Debug
    if (light_sensor_controller_debugMode)
    {
        debug_print_w_prefix("light_sensor_controller_init","finished");
    }
    //EndOfDebug
}

uint16_t light_sensor_controller_makeReading(){

    //Debug
    if (light_sensor_controller_debugMode)
    {
        debug_print_w_prefix("light_sensor_controller_makeReading","called");
    }
    //EndOfDebug

    uint16_t reading = light_read();

    //Debug
    if (light_sensor_controller_debugMode)
    {
        debug_print_w_uint_16("light_sensor_controller_makeReading with reading",reading);
    }
    //EndOfDebug

    return reading;
}