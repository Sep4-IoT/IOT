/// @brief This is a module that intitialises com port 0 to communicate with computer
/// to display all the aplication layer calls being made for debugging.
#pragma once // makes sure that header fire is incluced only once
#include "window.h"


#ifndef DECODER_H
#define DECODER_H

enum COMMUNICATION_PATTERN_t {
    ACK_GID_SEN_VAL,
    ACK_GID_ECHO,
    RES_GID_SEN_VAL,
    UPD_GID_POST_SEN_VAL,
    WAR_GID_VAL
};

#endif // DECODER_H


void decoder_decode(const char *message);
void decoder_send ( char* message, enum COMMUNICATION_PATTERN_t pattern, int sensor, uint16_t *value);
