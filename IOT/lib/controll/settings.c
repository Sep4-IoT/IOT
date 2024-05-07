#include <stdbool.h>
#include "includes.h"

//Module debug modes
bool window_debugMode = true;
bool decoder_debugMode = true;
bool wifi_controller_debugMode = true;

//Global easilly acessable settings
char greenhouseId[] = "10"; // greenhouse id
char *AP_SSID = "augustinas";
char *AP_PSWD = "asdfghjk";
char *ServerIP = "192.168.15.40";
uint16_t  ServerPort = 23;