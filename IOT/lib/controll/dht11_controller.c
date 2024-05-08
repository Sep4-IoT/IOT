#include <stdint.h>
#include "dht11_controller.h"
#include "debug.h"

extern bool dht11_debugMode;
static uint8_t temp_hum[4];

/**
 * @brief Get temperature and humidity readings
 *
 * This function obtains the temperature/humidity values from the dht11 driver and returns them in form of 4-element integer array.
 */
uint8_t* dht11_controller_get_temperature_humidity()
{
    uint8_t humidity_integer, humidity_decimal, temperature_integer, temperature_decimal;

    dht11_init();
    dht11_get(&humidity_integer, &humidity_decimal, &temperature_integer, &temperature_decimal);

    temp_hum[0] = temperature_decimal;
    temp_hum[1] = temperature_integer;
    temp_hum[2] = humidity_decimal;
    temp_hum[3] = humidity_integer;

    if (dht11_debugMode)
    {
        char debugMessage[100];
        sprintf(debugMessage, "New dht11 readings: temperature: %u.%u°C, humidity: %u.%u%%RH", temperature_decimal, temperature_integer, humidity_decimal, humidity_integer);
    }

    return temp_hum;
}
