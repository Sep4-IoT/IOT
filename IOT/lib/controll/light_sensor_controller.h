/// @brief module is reponsible for managing the light sensor
#ifndef LIGHT_SENSOR_CONTROLLER_H
#define LIGHT_SENSOR_CONTROLLER_H
#include <includes.h>

//Interfaces initialisiation of light sensor
void light_sensor_controller_init(); 

//Interfaces making a reading
inline uint16_t light_sensor_controller_makeReading();

#endif /* LIGHT_SENSOR_CONTROLLER_H */