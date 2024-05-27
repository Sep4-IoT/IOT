#include <unity.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "includes.h"
#include "fff.h"
// #include "mock_avr_io.h"
#include "debug.h"
#include "dht11_controller.h"
#include "light_sensor_controller.h"
#include "wifi_controller.h"
#include "window.h"
#include "dht11.h"
#include "light.h"
#include "servo.h"
#include "wifi.h"
#ifndef WINDOWS_TEST
DEFINE_FFF_GLOBALS

void setup(){FFF_RESET_HISTORY();} 
void teardown (){}

printf("Env: Target\n");

FAKE_VOID_FUNC(debug_print, const char*);
FAKE_VOID_FUNC(debug_print_w_uint_16, const char*, const uint16_t*);
FAKE_VOID_FUNC(debug_print_w_int, const char*, const int*);
FAKE_VALUE_FUNC(int, window_getState);
FAKE_VOID_FUNC(dht11_init);
FAKE_VALUE_FUNC(DHT11_ERROR_MESSAGE_t, dht11_get, uint8_t*, uint8_t*, uint8_t*, uint8_t*);
FAKE_VOID_FUNC(light_init);
FAKE_VALUE_FUNC(uint16_t, light_read);
FAKE_VOID_FUNC(wifi_init);
FAKE_VALUE_FUNC(WIFI_ERROR_MESSAGE_t, wifi_command_join_AP, char*, char*);
FAKE_VALUE_FUNC(WIFI_ERROR_MESSAGE_t, wifi_command_quit_AP);
FAKE_VALUE_FUNC(WIFI_ERROR_MESSAGE_t, wifi_command_create_TCP_connection, char*, uint16_t, WIFI_TCP_Callback_t, char*);
FAKE_VALUE_FUNC(WIFI_ERROR_MESSAGE_t, wifi_command_close_TCP_connection);
FAKE_VALUE_FUNC(WIFI_ERROR_MESSAGE_t, wifi_command_TCP_transmit, uint8_t*, uint16_t);
FAKE_VOID_FUNC(servo_set_angle, uint8_t);

void test_debug_target()
{
    uint16_t value = 25;
    int int_value = 18;
    debug_print_w_prefix("abcd", "Test:"); 
    TEST_ASSERT_EQUAL(1, debug_print_fake.call_count); //ERR
    TEST_ASSERT_EQUAL_STRING("Test: abcd", debug_print_fake.arg0_val);
    // debug_print_w_uint_16_fake("Test:", &value); // Placeholder for test with variables
    // TEST_ASSERT_EQUAL_STRING("Test: 25", debug_print_w_uint_16_fake.arg0_val);
    // debug_print_w_int_fake("Test:", &int_value); // Placeholder for test with variables
    // TEST_ASSERT_EQUAL_STRING("Test: 18", debug_print_w_int_fake.arg0_val);
}

void test_dht11_controller_target()
{
    dht11_controller_init();
    TEST_ASSERT_EQUAL(1, dht11_init_fake.call_count);
    dht11_controller_get_temperature_humidity();
    TEST_ASSERT_EQUAL(1, dht11_get_fake.call_count);
    TEST_ASSERT_NOT_EQUAL(0, dht11_get_fake.return_val);
}

void test_light_sensor_controller_target()
{
    light_sensor_controller_init();
    TEST_ASSERT_EQUAL(1, light_init_fake.call_count);
    light_sensor_controller_makeReading();
    TEST_ASSERT_EQUAL(1, light_read_fake.call_count);
    TEST_ASSERT_NOT_NULL(light_read_fake.return_val);
}

void test_wifi_controller_target()
{
    wifi_controller_initialise_wifi_module();
    TEST_ASSERT_EQUAL(1, wifi_init_fake.call_count);
    wifi_controller_connect_to_ap();
    TEST_ASSERT_EQUAL(1, wifi_command_join_AP_fake.call_count);
    wifi_controller_connect_to_tcp();
    TEST_ASSERT_EQUAL(1, wifi_command_create_TCP_connection_fake.call_count);
    wifi_controller_send_message("Test");
    TEST_ASSERT_EQUAL(1, wifi_command_TCP_transmit_fake.call_count);
    TEST_ASSERT_NOT_NULL(wifi_command_TCP_transmit_fake.arg0_val);
    TEST_ASSERT_EQUAL(50, wifi_command_TCP_transmit_fake.arg1_val);
    wifi_controller_disconnect_from_tcp();
    TEST_ASSERT_EQUAL(1, wifi_command_close_TCP_connection_fake.call_count);
    wifi_controller_disconnect_from_ap();
    TEST_ASSERT_EQUAL(1, wifi_command_quit_AP_fake.call_count);
}

void test_window_target()
{
    window_open();
    TEST_ASSERT_EQUAL(1, servo_set_angle_fake.call_count);
    TEST_ASSERT_EQUAL(180, servo_set_angle_fake.arg0_val);
    window_close();
    TEST_ASSERT_EQUAL(2, servo_set_angle_fake.call_count); 
    TEST_ASSERT_EQUAL(0, servo_set_angle_fake.arg0_val);
    window_open_at_angle(100);
    TEST_ASSERT_EQUAL(3, servo_set_angle_fake.call_count); //ERR
    TEST_ASSERT_EQUAL(100, servo_set_angle_fake.arg0_val);
    int state = window_get_state();
    TEST_ASSERT_NOT_NULL(&state); 
}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_debug_target);
    RUN_TEST(test_dht11_controller_target);
    RUN_TEST(test_light_sensor_controller_target);
    RUN_TEST(test_wifi_controller_target);
    RUN_TEST(test_window_target);
    return UNITY_END();
}
#endif