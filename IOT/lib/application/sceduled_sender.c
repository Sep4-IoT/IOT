#include "sceduled_sender.h"
#include "light_sensor_controller.h"
#include "dht11_controller.h"



// Task for sending all readings
void sceduled_sender_TaskSendAllReadings(){

    sceduled_sender_TaskSendLightReading();
    delay(100);
    sceduled_sender_TaskSendHumidityReading();
    delay(100);
    sceduled_sender_TaskSendTemperatureReading();
    delay(100);
    
}

// Tries to send only light reading
void sceduled_sender_TaskSendLightReading(){
    //void decoder_send (const char* message
    //, enum COMMUNICATION_PATTERN_t pattern, int sensor, 
    // const int *value)
        uint16_t light_value = light_sensor_controller_makeReading();
        decoder_send("", UPD_GID_POST_SEN_VAL, 1, (const int *)&light_value);
}

// Tries to send only humidity reading
void sceduled_sender_TaskSendHumidityReading(){
    //void decoder_send (const char* message
    //, enum COMMUNICATION_PATTERN_t pattern, int sensor, 
    // const int *value)
        int humidity = dht11_controller_get_temperature_humidity()[1]; 
        decoder_send("", UPD_GID_POST_SEN_VAL, 2, (const int)&humidity);
}

// Tries to send only temperature reading
void sceduled_sender_TaskSendTemperatureReading(){
        int temperature = dht11_controller_get_temperature_humidity()[3]; 
        decoder_send("", UPD_GID_POST_SEN_VAL, 4, (const int)&temperature);
}