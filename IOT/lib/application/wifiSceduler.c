#include "wifiSceduler.h"
#include "display.h"
#include <util/delay.h>



// Initialisation of module, where wifi and ip info is already set, module connects to wifi with given global data
void wifiSceduler_initialise(){
    wifi_controller_initialise_wifi_module();
    wifi_controller_connect_to_ap();
    wifi_controller_connect_to_tcp();
}

// Check if connectivity is OK otherwise try to reestablish it
void wifiSceduler_RecconectionTask(){
    debug_print("Checking wifi \n");
    
    char url[] = "www.google.com";  // The URL you want to resolve
    char ip_address[16];
    WIFI_ERROR_MESSAGE_t result;
    const char msg[50];

        result = wifi_command_get_ip_from_URL(url, ip_address);

        switch (result) {
        case WIFI_OK:
            //sprintf(msg,"IP address: %s\n", ip_address);
            break;
        default:
            wifi_controller_disconnect_from_tcp();
            wifi_controller_disconnect_from_ap();
            wifi_controller_connect_to_ap();
            wifi_controller_connect_to_tcp();
            break;

        }
}

