#include "sceduled_sender.h"
#include "light_sensor_controller.h"
#include "dht11_controller.h"
#include <avr/interrupt.h>

static uint8_t* dht11_readings[4];

extern sceduled_sender_debugMode;

// Task for sending all readings
void sceduled_sender_TaskSendAllReadings(){ //is interup rutine (from periodic function)
    // Debug prinoutout for sceduled task
    if(sceduled_sender_debugMode){debug_print("Sceduled sender started task");}

    sceduled_sender_TaskSendLightReading();
    cli(); // making reading uninteruptable routine
    sceduled_sender_TaskGetdht11Readings();
    sei(); // making reading uninteruptable routine
        // Requires readings to be taken first
        sceduled_sender_TaskSendHumidityReading();
        // Requires readings to be taken first
        sceduled_sender_TaskSendTemperatureReading();
    

    // Debug prinoutout for sceduled task
    if(sceduled_sender_debugMode){debug_print("Sceduled sender finished task");}
}
void sceduled_sender_TaskGetdht11Readings(){    // NEEDS FIXING, UNSURE WHY ONLY FIRST VALUE GETS SAVED
        
        uint8_t* temp_hum_ptr = dht11_controller_get_temperature_humidity();
        
        for (int i = 0; i < 4; ++i) 
        {
            dht11_readings[i] = temp_hum_ptr[i];
            // Debug printout for measurements
            if(sceduled_sender_debugMode){debug_print_w_uint_8("readings: ", &dht11_readings[i]);}
        }   
}

// Tries to send only light reading
void sceduled_sender_TaskSendLightReading(){
    //void decoder_send (const char* message
    //, enum COMMUNICATION_PATTERN_t pattern, int sensor, 
    // const int *value)
        
        uint16_t light_value = light_sensor_controller_makeReading();
        decoder_send("", UPD_GID_POST_SEN_VAL, 1, &light_value);
        
}

// Tries to send only humidity reading
void sceduled_sender_TaskSendHumidityReading(){
    //void decoder_send (const char* message
    //, enum COMMUNICATION_PATTERN_t pattern, int sensor, 
    // const int *value)
        //int humidity = (dht11_controller_get_temperature_humidity())[1]; 
        decoder_send("", UPD_GID_POST_SEN_VAL, 2, &dht11_readings[0]);
        //aaa
}

// Tries to send only temperature reading
void sceduled_sender_TaskSendTemperatureReading(){
     // to disable interrupt  // the interupts
        //int temperature = (dht11_controller_get_temperature_humidity())[3]; 
        decoder_send("", UPD_GID_POST_SEN_VAL, 4, &dht11_readings[2]);
    
}