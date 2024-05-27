#include <stdbool.h>
#include <stdint.h>

//Module debug modes
bool window_debugMode = false;
bool decoder_debugMode = false;
bool dht11_debugMode = false;
bool wifi_controller_debugMode = true; // maybe this one
bool light_sensor_controller_debugMode = false;
bool sceduled_sender_debugMode = true; // this for sure

//Global easilly acessable settings
char greenhouseId[] = "1"; // greenhouse id
char *AP_SSID = "augustinas";
char *AP_PSWD = "asdfghjk";
//char *ServerIP = "154.62.108.77";
//uint16_t  ServerPort = 50000;

char *ServerIP = "192.168.187.40";
uint16_t  ServerPort = 23;
