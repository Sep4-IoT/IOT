#pragma once
#include "wifi_controller.h"
//#include "settings.c"

// Initialisation of module, where wifi and ip info is already set, module connects to wifi with given global data
void wifiSceduler_initialise();

// Check if connectivity is OK otherwise try to reestablish it
void wifiSceduler_RecconectionTask();

// Returns true if wifi is connected
bool wifiSceduler_wifiConnected();

// Returns true if TCP connection is established
bool wifiSceduler_TCP_connected();