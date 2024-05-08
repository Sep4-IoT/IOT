#include "debug.h"
#include "window.h"
#include "dht11_controller.h"
#include <stddef.h> 
#include <string.h>
#include <stdbool.h>
#include "decoder.h"
#include "settings.c"
#include <stdio.h>


extern bool decoder_debugMode;
extern char greenhouseId[];

enum COMMUNICATION_PATTERN_t;

// only care about readability and maintainability

void decoder_decode(const char *message) {
    // TOKEN: this code splits saves request fields into an array
    if (decoder_debugMode)
    {
        debug_print_w_prefix(message, "debug");
    }
    const char delimiter[] = ",";
    char tokens[5][10];
    int num_tokens = 0;

    char *token = strtok(message, delimiter);
    while (token != NULL && num_tokens < 5)
    {
        strncpy(tokens[num_tokens], token, 9);
        tokens[num_tokens][9] = '\0';
        num_tokens++;
        token = strtok(NULL, delimiter);
    }
    // /TOKEN

    // Incoming types: T0: REQ,ACK; T2: SET,GET,ECHO; T3: SER,LIG,HUM,CO2,TEM
    // Outgoing types: T0: T0: ACK,RES,UPD,WAR; T2: T2: POST,ECHO; T3: T3: SER,LIG,HUM,CO2,TEM

    // Incoming type comparisons
    int t0_is_req = strcmp(tokens[0], "REQ");
    int t0_is_ack = strcmp(tokens[0], "ACK");

    int t2_is_get = strcmp(tokens[2], "GET");
    int t2_is_set = strcmp(tokens[2], "SET");
    int t2_is_echo = strcmp(tokens[2], "ECHO");

    int t3_is_ser = strcmp(tokens[3], "SER");
    int t3_is_lig = strcmp(tokens[3], "LIG");
    int t3_is_hum = strcmp(tokens[3], "HUM");
    int t3_is_co2 = strcmp(tokens[3], "CO2");
    int t3_is_tem = strcmp(tokens[3], "TEM");
    
    // Set new option for a sensor
    if (t0_is_req == 0 && t2_is_set == 0 && t3_is_ser == 0) //In: REQ,gid,SET,SER,val
    {
        int angle = atoi(tokens[4]); //Converting angle which is the 5th parameter of REQ,gid,SET,SER,val
        window_open_at_angle(angle);
        decoder_send(message, ACK_GID_SEN_VAL, 0, window_get_state());
    }
    // Request for sensor data
    else if (t0_is_req == 0 && t2_is_get == 0 && t3_is_ser == 0) //In: REQ,gid,GET,SER
    {
        decoder_send(message, RES_GID_SEN_VAL, 0, window_get_state());
    }
    else if (t0_is_req == 0 && t2_is_get == 0 && t3_is_tem == 0)
    {
        uint8_t temp_hum[4];
        uint8_t* temp_hum_ptr = dht11_controller_get_temperature_humidity();
        for (int i = 0; i < 4; ++i) 
        {
            temp_hum[i] = temp_hum_ptr[i];
        }
        int temperature = temp_hum[0] * 10 + temp_hum[1]; //Constructing temperature from response array
        decoder_send(message, RES_GID_SEN_VAL, 4, temperature);
    }
    else if (t0_is_req == 0 && t2_is_get == 0 && t3_is_hum == 0)
    {
        uint8_t temp_hum[4];
        uint8_t* temp_hum_ptr = dht11_controller_get_temperature_humidity();
        for (int i = 0; i < 4; ++i) 
        {
            temp_hum[i] = temp_hum_ptr[i];
        }
        int humidity = temp_hum[2] * 10 + temp_hum[3]; //Constructing humidity from response array
        decoder_send(message, RES_GID_SEN_VAL, 4, humidity);
    }
    // Echo for connectivity response
    else if (t0_is_req == 0 && t2_is_echo == 0) //In: REQ,gid,ECHO
    {
        decoder_send(message, ACK_GID_ECHO, NULL, NULL);
    }
}

// SENSOR LEGEND: SER=0, LIG=1, HUM=2, CO2=3, TEM=4
// DEBUG LEGEND: FALSE=0, TRUE=1
void decoder_send (const char* message, enum COMMUNICATION_PATTERN_t pattern, int sensor, int value)
{
    char answer[50];
    if (pattern == ACK_GID_SEN_VAL)
    {
        switch (sensor)
        {
            case 0:
                sprintf(answer, "ACK,%s,SER,%u", greenhouseId, value);
                break;
            case 1:
                sprintf(answer, "ACK,%s,LIG,%u", greenhouseId, value);
                break;
            case 2:
                sprintf(answer, "ACK,%s,HUM,%u", greenhouseId, value);
                break;
            case 3:
                sprintf(answer, "ACK,%s,CO2,%u", greenhouseId, value);
                break;
            case 4:
                sprintf(answer, "ACK,%s,TEM,%u", greenhouseId, value);
                break;
        }
    }
    else if (pattern == ACK_GID_ECHO)
    {
        sprintf(answer, "ACK,%s,ECHO", greenhouseId);
    }
    else if (pattern == RES_GID_SEN_VAL)
    {
        switch (sensor)
        {
            case 0:
                sprintf(answer, "RES,%s,SER,%u", greenhouseId, value); 
                break;
            case 1:
                sprintf(answer, "RES,%s,LIG,%u", greenhouseId, value); 
                break;
            case 2:
                sprintf(answer, "RES,%s,HUM,%u", greenhouseId, value); 
                break;
            case 3:
                sprintf(answer, "RES,%s,CO2,%u", greenhouseId, value);     
                break;
            case 4:
                sprintf(answer, "RES,%s,TEM,%u", greenhouseId, value);  
                break;
        }
    }
    else if (pattern == UPD_GID_POST_SEN_VAL)
    {
        switch (sensor)
        {
            case 0:
                sprintf(answer, "UPD,%s,POST,SER,%u", greenhouseId, value); 
                break;
            case 1:
                sprintf(answer, "UPD,%s,POST,LIG,%u", greenhouseId, value); 
                break;
            case 2:
                sprintf(answer, "UPD,%s,POST,HUM,%u", greenhouseId, value); 
                break;
            case 3:
                sprintf(answer, "UPD,%s,POST,CO2,%u", greenhouseId, value);   
                break;
            case 4:
                sprintf(answer, "UPD,%s,POST,TEM,%u", greenhouseId, value); 
                break;
        }
    }
    else if (pattern == WAR_GID_VAL)
    {
        sprintf(answer, "ACK,%s", greenhouseId);
    }

    wifi_controller_send_message(answer);

    if (decoder_debugMode == true)
{
    switch (pattern){ // Corrected
        case ACK_GID_SEN_VAL:
        case ACK_GID_ECHO:
            debug_print_w_prefix(answer, "ACK message sent"); 
            break;
        case RES_GID_SEN_VAL:
            debug_print_w_prefix(answer, "RES message sent"); 
            break;    
        case UPD_GID_POST_SEN_VAL:
            debug_print_w_prefix(answer, "UPD message sent"); 
            break;    
        case WAR_GID_VAL:
            debug_print_w_prefix(answer, "WAR message sent"); 
            break;  
            }
}
}

// OLD CODE:
// char *substring = strstr(message, "REQ,10,SET,SER,");
//     if (substring != NULL) {
//         // Check if the substring is at the beginning of the message


//         if (substring == message) {
//             // Extract the last part of the message as an integer
//             int windowOpenAngle;
//             if (sscanf(message + strlen("REQ,10,SET,SER,"), "%d", &windowOpenAngle) == 1) {
//                 window_open_at_angle(windowOpenAngle);

//                 char answer[50]; // "ACK,{Greenhouse id},{Sensor},{Answer}"
//                 sprintf(answer, "ACK,%s,SER,%u" , greenhouseId,window_get_state()); 

//                 wifi_controller_send_message(answer);

//                 if (decoder_debugMode) {
//                     debug_print_w_prefix(debugMessage, "ACK message sent"); 
//                 }

//             }
//         }
//     }