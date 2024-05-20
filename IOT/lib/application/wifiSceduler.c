#include "wifiSceduler.h"
#include "display.h"



extern char greenhouseId[];

// Initialisation of module, where wifi and ip info is already set, module connects to wifi with given global data
void wifiSceduler_initialise(){
    wifi_controller_initialise_wifi_module();
    wifi_controller_connect_to_ap();
    wifi_controller_connect_to_tcp();
}

// Check if connectivity is OK otherwise try to reestablish it
void wifiSceduler_RecconectionTask(){
    debug_print_w_prefix("Connection check fired","");
    // Redundancy check, if we are still connected
    if(!wifiSceduler_wifiConnected){
        wifi_controller_connect_to_ap();
        debug_print_w_prefix("Recconecting to AP","");
        display_setValues(1,1,1,1);
    }
    if(!wifiSceduler_TCP_connected){
        wifi_controller_connect_to_tcp();
        debug_print_w_prefix("Recconecting to TCP","");
        display_setValues(2,2,2,2);
    }
}

// Returns true if wifi is connected
bool wifiSceduler_wifiConnected(){
    WIFI_ERROR_MESSAGE_t error = wifi_controller_commandAT();
    return error == WIFI_OK;
}

// Returns true if TCP connection is established and tcp is able to send a ping rqeust, disregards reponse
bool wifiSceduler_TCP_connected(){
    // Implement TCP connection check using wifi_command_TCP_transmit as a test
    char testMessage[128];
    snprintf(testMessage, sizeof(testMessage), "REQ,%s,ECHO", greenhouseId);

    debug_print("REQ ECHO fired \n");
    
    WIFI_TCP_Callback_t dummyCallback = NULL;
    char dummyBuffer[128]; // Define a dummy buffer to receive potential messages 
    if (wifiSceduler_wifiConnected) {

        WIFI_ERROR_MESSAGE_t error = wifi_command_TCP_transmit(testMessage, sizeof(testMessage));
        
        if (error == WIFI_OK) {
            // TCP connection is considered established if message transmission succeeds
            debug_print("WIFI OK \n");
            return true;
        }
    }
    debug_print("WIFI ISSUE \n");
    return false;
}