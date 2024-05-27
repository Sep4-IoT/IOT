#include <unity.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "includes.h"
#include "fff.h"
// #include "mock_avr_io.h"
#include "debug.h"
#include "decoder.h"
#include "dht11_controller.h"
#include "light_sensor_controller.h"
#include "wifi_controller.h"
#include "window.h"
#include "dht11.h"
#include "light.h"
#include "servo.h"
#include "wifi.h"
#define WINDOWS_TEST
#ifdef WINDOWS_TEST
DEFINE_FFF_GLOBALS



void setup(){FFF_RESET_HISTORY();} 
void teardown (){}

printf("Env: Native\n");
#endif