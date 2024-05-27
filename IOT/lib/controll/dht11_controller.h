#ifndef DHT11_CONTROLLER_H
#define DHT11_CONTROLLER_H
#include <stdint.h>
#include "dht11.h"

void dht11_controller_init();
inline uint8_t* dht11_controller_get_temperature_humidity();

#endif /* DHT11_CONTROLLER_H */