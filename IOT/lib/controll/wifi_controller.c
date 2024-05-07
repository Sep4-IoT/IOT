#include "wifi.h"
#include "wifi_controller.h"
#include "debug.h"
#include <stdbool.h>
#include <stdio.h>
#include "decoder.h"

// wifi controloler rename
//name convention wifiModule_initialiseWifiModule;
//class diagram
// naming variables wifiModule_AP_SSID;


extern bool wifi_controller_debugMode;
extern char *AP_SSID;
extern char *AP_PSWD;
extern char *ServerIP;
extern uint16_t ServerPort;

char receivedMessage[50];

// initialisation of module
void wifi_controller_initialise_wifi_module(){
    wifi_init();
    if(wifi_controller_debugMode){debug_print("wifiModule initialised \n");}
    
}

// changing credentials/server ip
void wifi_controller_set_ap_ssid(const char *SSID) {
    AP_SSID = SSID;
    if (wifi_controller_debugMode) {
        char debugMessage[50];
        sprintf(debugMessage, "setAP_SSID %s  \n", AP_SSID);
        debug_print(debugMessage);
    }
}
void wifi_controller_set_ap_pswd(const char *PSWD) {
    AP_PSWD = PSWD;
    if (wifi_controller_debugMode) {
        char debugMessage[50];
        sprintf(debugMessage, "setAP_PSWD %s  \n", AP_PSWD);
        debug_print(debugMessage);
    }
}
void wifi_controller_set_server_ip(const char *IP) {
    ServerIP = IP;
    if (wifi_controller_debugMode) {
        char debugMessage[50];
        sprintf(debugMessage, "setServerIP %s  \n", ServerIP);
        debug_print(debugMessage);
    }
}

void wifi_controller_set_server_port(const uint16_t *Port) {
    ServerPort = Port;
    if (wifi_controller_debugMode) {
        char portString[6]; // Assuming 5 characters for the port number plus null terminator
        // Convert uint8_t ServerPort to string
        sprintf(portString, "%u", ServerPort);
        char debugMessage[50];
        sprintf(debugMessage, "setServerPort %s  \n", portString);
        debug_print(debugMessage);
    }
}

// connectivity management
void wifi_controller_connect_to_ap(){

    if(wifi_controller_debugMode){
        char debugMessage[50]; // Assuming the message won't exceed 50 characters
        sprintf(debugMessage, "connectToAP SSID:%s PSWD:%s \n", AP_SSID, AP_PSWD);
        debug_print(debugMessage);
        }

    if (WIFI_OK==wifi_command_join_AP(AP_SSID,AP_PSWD))  
        if(wifi_controller_debugMode){debug_print("Joined AP \n");}
    else 
        if(wifi_controller_debugMode){debug_print("Failed to join AP \n");}
}
void wifi_controller_disconnect_from_ap(){
    wifi_command_quit_AP();
    if(wifi_controller_debugMode){debug_print("Disconected from AP \n");}
}
void wifi_controller_connect_to_tcp(){
    if(wifi_controller_debugMode){
        char portString[6]; // Assuming 5 characters for the port number plus null terminator
        // Convert uint8_t ServerPort to string
        sprintf(portString, "%u", ServerPort);
        char debugMessage[50]; // Assuming the message won't exceed 50 characters
        sprintf(debugMessage, "connectToTCP %s:%s \n", ServerIP, portString);
        debug_print(debugMessage);
    }


    if (WIFI_OK == wifi_command_create_TCP_connection(ServerIP,ServerPort, wifi_controller_callback, receivedMessage))  // use this for callback and deciphering callback
        if(wifi_controller_debugMode){debug_print("Joined TCP connection\n");}
    else
        if(wifi_controller_debugMode){debug_print("Failed connecting tcp\n");}
        
}
void wifi_controller_disconnect_from_tcp(){
    
    wifi_command_close_TCP_connection();
    if(wifi_controller_debugMode){debug_print("disconnectFromTCP\n");}
}

// sending messages
void wifi_controller_send_message(const char *message){
    char paddedMessage[50]; // Assuming the maximum length of the message is 50 characters

    // Copy the message to paddedMessage and pad with null characters if necessary
    size_t messageLength = strlen(message);
    if (messageLength < 50) {
        strcpy(paddedMessage, message);
        memset(paddedMessage + messageLength, '\0', 50 - messageLength);
    } else {
        strncpy(paddedMessage, message, 50);
    }

    // Transmit the padded message
    wifi_command_TCP_transmit((uint8_t *)paddedMessage, 50);

    if (wifi_controller_debugMode) {
        char debugMessage[50];
        sprintf(debugMessage, "sendMessage \' %s \' \n", message);
        debug_print(debugMessage);
    }
}

// callback function
void wifi_controller_callback(){
    if(wifi_controller_debugMode){
        char debugMessage[50]; // Assuming the message won't exceed 50 characters
        sprintf(debugMessage,"recieved message: %s \n" , receivedMessage);
        debug_print(debugMessage);
    }
    decoder_decode(receivedMessage);
    
}