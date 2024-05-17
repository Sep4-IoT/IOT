#include "wifiSceduler.h"
#include "decoder.h"

// Task for sending all readings
void sceduled_sender_TaskSendAllReadings();

// Tries to send only light reading
void sceduled_sender_TaskSendLightReading();

// Tries to send only humidity reading
void sceduled_sender_TaskSendHumidityReading();

// Tries to send only temperature reading
void sceduled_sender_TaskSendTemperatureReading();