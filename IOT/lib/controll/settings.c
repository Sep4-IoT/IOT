#include <stdbool.h>
#include <stdint.h>

//Module debug modes
bool window_debugMode = true;
bool decoder_debugMode = true;
bool dht11_debugMode = true;
bool wifi_controller_debugMode = true;
bool light_sensor_controller_debugMode = true;

//Global easilly acessable settings
char greenhouseId[] = "10"; // greenhouse id
char *AP_SSID = "augustinas";
char *AP_PSWD = "asdfghjk";
//char *ServerIP = "154.62.108.77";
//uint16_t  ServerPort = 50000;

char *ServerIP = "192.168.187.40";
uint16_t  ServerPort = 23;