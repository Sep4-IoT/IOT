#include <unity.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "fff.h"
// #include "mock_avr_io.h"
#include "debug.h"
#include "decoder.h"
#include "dht11_controller.h"
#include "light_sensor_controller.h"
#include "window.h"
#ifndef WINDOWS_TEST
DEFINE_FFF_GLOBALS

bool decoder_debugMode;
enum COMMUNICATION_PATTERN_t;

void setup(){FFF_RESET_HISTORY();} 
void teardown (){}

printf("Env: Target\n");

FAKE_VOID_FUNC(debug_print_w_prefix, const char*, const char*);
FAKE_VOID_FUNC(debug_print_w_int, const char*, const int*);
FAKE_VOID_FUNC(window_open_at_angle, uint8_t);
FAKE_VALUE_FUNC(int, window_getState);
FAKE_VOID_FUNC(decoder_send, const char*, enum COMMUNICATION_PATTERN_t, int, const int*);
FAKE_VALUE_FUNC(uint8_t*, dht11_controller_get_temperature_humidity);
FAKE_VALUE_FUNC(uint16_t, light_sensor_controller_makeReading);

void test_decoder_target()
{
    decoder_debugMode = true;
    decoder_decode("REQ,10,SET,SER,100");
    TEST_ASSERT_EQUAL(1, debug_print_w_prefix_fake.call_count);
    TEST_ASSERT_EQUAL_STRING("REQ,10,SET,SER,100", debug_print_w_prefix_fake.arg0_val);
    TEST_ASSERT_EQUAL_STRING("debug", debug_print_w_prefix_fake.arg1_val);
    TEST_ASSERT_EQUAL(1, debug_print_w_int_fake.call_count);
    decoder_debugMode = false;
    decoder_decode("REQ,10,SET,SER,100");
    TEST_ASSERT_EQUAL(0, debug_print_w_prefix_fake.call_count);
    TEST_ASSERT_EQUAL(1, window_open_at_angle_fake.call_count);
    TEST_ASSERT_EQUAL(1, window_getState_fake.call_count);
    TEST_ASSERT_EQUAL(1, decoder_send_fake.call_count);
    TEST_ASSERT_EQUAL_STRING("REQ,10,SET,SER,100", decoder_send_fake.arg0_val);
    TEST_ASSERT_EQUAL(RES_GID_SEN_VAL, decoder_send_fake.arg1_val);
    TEST_ASSERT_EQUAL(0, decoder_send_fake.arg2_val);
    TEST_ASSERT_EQUAL(100, decoder_send_fake.arg3_val);
    decoder_decode("REQ,10,GET,SER");
    TEST_ASSERT_EQUAL(1, window_getState_fake.call_count);
    TEST_ASSERT_EQUAL_STRING("REQ,10,GET,SER", decoder_send_fake.arg0_val);
    TEST_ASSERT_EQUAL(RES_GID_SEN_VAL, decoder_send_fake.arg1_val);
    TEST_ASSERT_EQUAL(0, decoder_send_fake.arg2_val);
    decoder_decode("REQ,10,GET,TEM");
    TEST_ASSERT_EQUAL(1, dht11_controller_get_temperature_humidity_fake.call_count);
    TEST_ASSERT_EQUAL_STRING("REQ,10,GET,TEM", decoder_send_fake.arg0_val);
    TEST_ASSERT_EQUAL(RES_GID_SEN_VAL, decoder_send_fake.arg1_val);
    TEST_ASSERT_EQUAL(4, decoder_send_fake.arg2_val);
    decoder_decode("REQ,10,GET,HUM");
    TEST_ASSERT_EQUAL(1, dht11_controller_get_temperature_humidity_fake.call_count);
    TEST_ASSERT_EQUAL_STRING("REQ,10,GET,HUM", decoder_send_fake.arg0_val);
    TEST_ASSERT_EQUAL(RES_GID_SEN_VAL, decoder_send_fake.arg1_val);
    TEST_ASSERT_EQUAL(2, decoder_send_fake.arg2_val);
    decoder_decode("REQ,10,GET,LIG");
    TEST_ASSERT_EQUAL(1, light_sensor_controller_makeReading_fake.call_count);
    TEST_ASSERT_EQUAL_STRING("REQ,10,GET,LIG", decoder_send_fake.arg0_val);
    TEST_ASSERT_EQUAL(RES_GID_SEN_VAL, decoder_send_fake.arg1_val);
    TEST_ASSERT_EQUAL(1, decoder_send_fake.arg2_val);
    decoder_decode("REQ,10,ECHO");
    TEST_ASSERT_EQUAL_STRING("REQ,10,ECHO", decoder_send_fake.arg0_val);
    TEST_ASSERT_EQUAL(ACK_GID_ECHO, decoder_send_fake.arg1_val);
    TEST_ASSERT_NULL(decoder_send_fake.arg2_val);
    TEST_ASSERT_NULL(decoder_send_fake.arg3_val);
}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_decoder_target);
    return UNITY_END();
}
#endif