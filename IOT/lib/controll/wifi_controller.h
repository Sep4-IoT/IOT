/// @brief module is responsible for establishing and keeping connectivity, sending messages

// wifi controloler rename
#pragma once
#include "wifi.h"
#include "debug.h"

// initialisation of module
void wifi_controller_initialise_wifi_module();

// changing credentials/server ip
void wifi_controller_set_ap_ssid( char *message);
void wifi_controller_set_ap_pswd( char *message);
void wifi_controller_set_server_ip( char *IP);
void wifi_controller_set_server_port( uint16_t *Port);

// connectivity management
void wifi_controller_connect_to_ap();
void wifi_controller_disconnect_from_ap();
void wifi_controller_connect_to_tcp();
void wifi_controller_disconnect_from_tcp();

// sending messages
void wifi_controller_send_message( char *message);
void wifi_controller_callback();

// responsiveness
WIFI_ERROR_MESSAGE_t wifi_controller_commandAT();
