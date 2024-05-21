/// @brief module is reponsible for managing the light sensor
#pragma once
#include <includes.h>

//Interfaces initialisiation of light sensor
void light_sensor_controller_init(); 

//Interfaces making a reading
uint16_t light_sensor_controller_makeReading();