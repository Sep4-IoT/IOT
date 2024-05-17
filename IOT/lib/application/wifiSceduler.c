#include "wifiSceduler.h"

// Initialisation of module, where wifi and ip info is already set, module connects to wifi with given global data
void wifiSceduler_initialise(){
    wifi_controller_initialise_wifi_module();
    wifi_controller_connect_to_ap();
    wifi_controller_connect_to_tcp();
}

// Check if connectivity is OK otherwise try to reestablish it
void wifiSceduler_task(){
    // Redundancy check, if we are still connected
    if(!wifiSceduler_wifiConnected){
        wifi_controller_connect_to_ap();
    }
    if(!wifiSceduler_TCP_connected){
        wifi_controller_connect_to_tcp();
    }
}

// Returns true if wifi is connected
bool wifiSceduler_wifiConnected(){
    return true;
}

// Returns true if TCP connection is established
bool wifiSceduler_TCP_connected(){
    return true;
}