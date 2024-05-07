/// @brief module is responsible for establishing and keeping connectivity, sending messages

// wifi controloler rename

#include "wifi.h"
#include "debug.h"

// initialisation of module
void wifi_controller_initialise_wifi_module();

// changing credentials/server ip
void wifi_controller_set_ap_ssid(const char *message);
void wifi_controller_set_ap_pswd(const char *message);
void wifi_controller_set_server_ip(const char *IP);
void wifi_controller_set_server_port(const uint16_t *Port);

// connectivity management
void wifi_controller_connect_to_ap();
void wifi_controller_disconnect_from_ap();
void wifi_controller_connect_to_tcp();
void wifi_controller_disconnect_from_tcp();

// sending messages
void wifi_controller_send_message(const char *message);
void wifi_controller_callback();
