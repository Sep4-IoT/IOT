#include "sceduled_sender.h"
#include "light_sensor_controller.h"
#include "dht11_controller.h"
//#include "settings.c"
#include <avr/interrupt.h>


void sceduled_sender_TaskGetdht11Readings();

static uint16_t dht11_readings[4]; // static makes it persistent and protected

extern bool sceduled_sender_debugMode;

// Task for sending all readings
void sceduled_sender_TaskSendAllReadings(){ //is interup rutine (from periodic function)
    // Debug prinoutout for sceduled task
    if(sceduled_sender_debugMode){debug_print("Sceduled sender started task");}

    sceduled_sender_TaskSendLightReading();
    cli(); // making reading uninteruptable routine
    sceduled_sender_TaskGetdht11Readings();
    sei(); // making reading uninteruptable routine
        // Requires readings to be taken first
        sceduled_sender_TaskSendHumidityReading(); // Issues when debug is off
        
        // Requires readings to be taken first
        sceduled_sender_TaskSendTemperatureReading();
    

    // Debug prinoutout for sceduled task
    if(sceduled_sender_debugMode){debug_print("Sceduled sender finished task \n");}
}
void sceduled_sender_TaskGetdht11Readings(){    
        
        uint8_t* temp_hum_ptr = dht11_controller_get_temperature_humidity();
        
        for (int i = 0; i < 4; ++i) 
        {
            dht11_readings[i] = (uint16_t) temp_hum_ptr[i];     //rereferencing uint8 array to uint16 values from the first element in array of 4
            // Debug printout for measurements
            if(sceduled_sender_debugMode){debug_print_w_uint_8("readings: ", (uint8_t*) &dht11_readings[i]);}
        }   
}

// Tries to send only light reading
void sceduled_sender_TaskSendLightReading(){
        uint16_t light_value = light_sensor_controller_makeReading();
        decoder_send("", UPD_GID_POST_SEN_VAL, 1, &light_value);
        
}

// Tries to send only humidity reading
void sceduled_sender_TaskSendHumidityReading(){
        decoder_send("", UPD_GID_POST_SEN_VAL, 2, (uint16_t*) &dht11_readings[0]); // sending pointers to the elements to be used deeper in the code

        if(sceduled_sender_debugMode){debug_print("Task sceduled_sender_TaskSendHumidityReading called \n");}
       
}

// Tries to send only temperature reading
void sceduled_sender_TaskSendTemperatureReading(){
        decoder_send("", UPD_GID_POST_SEN_VAL, 4, (uint16_t*) &dht11_readings[2]); // sending pointers to the elements to be used deeper in the code

        if(sceduled_sender_debugMode){debug_print("Task sceduled_sender_TaskSendTemperatureReading called \n");}
}