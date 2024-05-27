#include <stdint.h>
#include "dht11_controller.h"
#include "debug.h"
#include <avr/interrupt.h>

extern bool dht11_debugMode;
static uint8_t temp_hum[4]; // Make it persistent

/**
 * @brief Get temperature and humidity readings
 *
 * This function obtains the temperature/humidity values from the dht11 driver and returns them in form of 4-element integer array.
 */

void dht11_controller_init(){
    dht11_init();
    if(dht11_debugMode){
        debug_print_w_prefix("dth11 ", "Initialised");
    }
}

uint8_t* dht11_controller_get_temperature_humidity()
{
     uint8_t humidity_integer, humidity_decimal, temperature_integer, temperature_decimal;

    //dht11_init();
    cli();
    dht11_get(&humidity_integer, &humidity_decimal, &temperature_integer, &temperature_decimal);
    sei();

    temp_hum[0] = humidity_integer;
    temp_hum[1] = humidity_decimal;
    temp_hum[2] = temperature_integer;
    temp_hum[3] = temperature_decimal;

    if (dht11_debugMode)
    {
        char debugMessage[100];
        sprintf(debugMessage, "New dht11 readings: temperature: %u.%u°C, humidity: %u.%u%%RH", temperature_integer, temperature_decimal, humidity_integer, humidity_decimal);
        debug_print_w_prefix(debugMessage,"Reading executed ");
    }

    return temp_hum;
}
