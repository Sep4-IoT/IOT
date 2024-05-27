// #include <unity.h>
// #include <string.h>
// #include <stdbool.h>
// #include "fff.h"
// // #include "mock_avr_io.h"
// #include "debug.h"
// #include "decoder.h"
// #include "dht11_controller.h"
// #include "light_sensor_controller.h"
// #include "wifi_controller.h"
// #include "window.h"
// #include "dht11.h"
// #include "light.h"
// #include "servo.h"
// #include "wifi.h"

// DEFINE_FFF_GLOBALS

// bool decoder_debugMode;
// enum COMMUNICATION_PATTERN_t;
// enum DHT11_ERROR_MESSAGE_t;
// enum WIFI_ERROR_MESSAGE_t;
// enum WIFI_TCP_Callback_t;
// enum USART_t;

// void setup(){FFF_RESET_HISTORY();} 
// // You are an idiot; we need fakes only when we don't want to have the real hardware involved, eg. with native testing
// // We could call real functions here and assert them with the same ASSERT statements (I think?) and it would get tested on target (i.e. Atmega)
// // Real functions are overwritten by faked ones 
// // 2 separate test.c files
// // No fake and real versions in the same test file
// // 2 subfolders within test folder (test_l1, test_l2) 
// // No drivers included natively 
// // AFTER MEETING - So what happened:
// // We can't both use a function and define it as a fake because the fake will overshadow the real function.
// // 2 approaches to this problem:
// // A1: Write 2 separate test files:
// // currently decoder_decode (real) -> debug_print_w_prefix (real, fake) -> debug_print (fake)
// // In the "inner" test file: debug_print_w_prefix (real) -> debug_print (fake)
// // In the "outer" test file: decoder_decode (real) -> debug_print_w_prefix (fake)
// // A2: replace the "intermediary" functions with calls to driver functions which will never be called as real; 
// // instead of decoder_decode (real) -> debug_print_w_prefix (real, fake) -> debug_print (fake)
// // do decoder_decode (real) -> uart_string_send_blocking; cut the middleman
// // But if we choose A2, we won't be able to test on native because you can't include the drivers in native (because in native 
// // everything is simulated and drivers are bound to specific hardware)
// void teardown (){}

// FAKE_VOID_FUNC(debug_print, const char*);
// FAKE_VOID_FUNC(debug_print_w_prefix, const char*, const char*);
// FAKE_VOID_FUNC(debug_print_w_uint_16, const char*, const uint16_t*);
// FAKE_VOID_FUNC(debug_print_w_int, const char*, const int*);
// FAKE_VOID_FUNC(decoder_send, const char*, enum COMMUNICATION_PATTERN_t, int, const int*);
// FAKE_VOID_FUNC(window_open_at_angle, uint8_t);
// FAKE_VALUE_FUNC(int, window_getState);
// FAKE_VALUE_FUNC(uint8_t*, dht11_controller_get_temperature_humidity);
// FAKE_VALUE_FUNC(uint16_t, light_sensor_controller_makeReading);
// FAKE_VOID_FUNC(dht11_init);
// FAKE_VALUE_FUNC(DHT11_ERROR_MESSAGE_t, dht11_get, uint8_t*, uint8_t*, uint8_t*, uint8_t*);
// FAKE_VOID_FUNC(light_init);
// FAKE_VALUE_FUNC(uint16_t, light_read);
// FAKE_VOID_FUNC(wifi_init);
// FAKE_VALUE_FUNC(WIFI_ERROR_MESSAGE_t, wifi_command_join_AP, char*, char*);
// FAKE_VALUE_FUNC(WIFI_ERROR_MESSAGE_t, wifi_command_quit_AP);
// FAKE_VALUE_FUNC(WIFI_ERROR_MESSAGE_t, wifi_command_create_TCP_connection, char*, uint16_t, WIFI_TCP_Callback_t, char*);
// FAKE_VALUE_FUNC(WIFI_ERROR_MESSAGE_t, wifi_command_close_TCP_connection);
// FAKE_VALUE_FUNC(WIFI_ERROR_MESSAGE_t, wifi_command_TCP_transmit, uint8_t*, uint16_t);
// FAKE_VOID_FUNC(servo_set_angle, uint8_t);

// // Control Layer tests
// void test_debug()
// {
//     uint16_t value = 25;
//     int int_value = 18;
//     debug_print_w_prefix("abcd", "Test:"); // Fake, should be real, cause of error
//     TEST_ASSERT_EQUAL(1, debug_print_fake.call_count); //ERR
//     TEST_ASSERT_EQUAL_STRING("Test: abcd", debug_print_fake.arg0_val);
//     debug_print_w_uint_16_fake("Test:", &value);
//     TEST_ASSERT_EQUAL_STRING("Test: 25", debug_print_w_uint_16_fake.arg0_val);
//     debug_print_w_int("Test:", &int_value);
//     TEST_ASSERT_EQUAL_STRING("Test: 18", debug_print_w_int_fake.arg0_val);
// }

// void test_decoder()
// {
//     decoder_debugMode = true;
//     decoder_decode("REQ,10,SET,SER,100");
//     TEST_ASSERT_EQUAL(1, debug_print_w_prefix_fake.call_count);
//     TEST_ASSERT_EQUAL_STRING("REQ,10,SET,SER,100", debug_print_w_prefix_fake.arg0_val);
//     TEST_ASSERT_EQUAL_STRING("debug", debug_print_w_prefix_fake.arg1_val);
//     TEST_ASSERT_EQUAL(1, debug_print_w_int_fake.call_count);
//     decoder_debugMode = false;
//     decoder_decode("REQ,10,SET,SER,100");
//     TEST_ASSERT_EQUAL(0, debug_print_w_prefix_fake.call_count);
//     TEST_ASSERT_EQUAL(1, window_open_at_angle_fake.call_count);
//     TEST_ASSERT_EQUAL(1, window_getState_fake.call_count);
//     TEST_ASSERT_EQUAL(1, decoder_send_fake.call_count);
//     TEST_ASSERT_EQUAL_STRING("REQ,10,SET,SER,100", decoder_send_fake.arg0_val);
//     TEST_ASSERT_EQUAL(RES_GID_SEN_VAL, decoder_send_fake.arg1_val);
//     TEST_ASSERT_EQUAL(0, decoder_send_fake.arg2_val);
//     TEST_ASSERT_EQUAL(100, decoder_send_fake.arg3_val);
//     decoder_decode("REQ,10,GET,SER");
//     TEST_ASSERT_EQUAL(1, window_getState_fake.call_count);
//     TEST_ASSERT_EQUAL_STRING("REQ,10,GET,SER", decoder_send_fake.arg0_val);
//     TEST_ASSERT_EQUAL(RES_GID_SEN_VAL, decoder_send_fake.arg1_val);
//     TEST_ASSERT_EQUAL(0, decoder_send_fake.arg2_val);
//     decoder_decode("REQ,10,GET,TEM");
//     TEST_ASSERT_EQUAL(1, dht11_controller_get_temperature_humidity_fake.call_count);
//     TEST_ASSERT_EQUAL_STRING("REQ,10,GET,TEM", decoder_send_fake.arg0_val);
//     TEST_ASSERT_EQUAL(RES_GID_SEN_VAL, decoder_send_fake.arg1_val);
//     TEST_ASSERT_EQUAL(4, decoder_send_fake.arg2_val);
//     decoder_decode("REQ,10,GET,HUM");
//     TEST_ASSERT_EQUAL(1, dht11_controller_get_temperature_humidity_fake.call_count);
//     TEST_ASSERT_EQUAL_STRING("REQ,10,GET,HUM", decoder_send_fake.arg0_val);
//     TEST_ASSERT_EQUAL(RES_GID_SEN_VAL, decoder_send_fake.arg1_val);
//     TEST_ASSERT_EQUAL(2, decoder_send_fake.arg2_val);
//     decoder_decode("REQ,10,GET,LIG");
//     TEST_ASSERT_EQUAL(1, light_sensor_controller_makeReading_fake.call_count);
//     TEST_ASSERT_EQUAL_STRING("REQ,10,GET,LIG", decoder_send_fake.arg0_val);
//     TEST_ASSERT_EQUAL(RES_GID_SEN_VAL, decoder_send_fake.arg1_val);
//     TEST_ASSERT_EQUAL(1, decoder_send_fake.arg2_val);
//     decoder_decode("REQ,10,ECHO");
//     TEST_ASSERT_EQUAL_STRING("REQ,10,ECHO", decoder_send_fake.arg0_val);
//     TEST_ASSERT_EQUAL(ACK_GID_ECHO, decoder_send_fake.arg1_val);
//     TEST_ASSERT_NULL(decoder_send_fake.arg2_val);
//     TEST_ASSERT_NULL(decoder_send_fake.arg3_val);
// }

// void test_dht11_controller()
// {
//     dht11_controller_init();
//     TEST_ASSERT_EQUAL(1, dht11_init_fake.call_count);
//     dht11_controller_get_temperature_humidity();
//     TEST_ASSERT_EQUAL(1, dht11_get_fake.call_count);
//     TEST_ASSERT_NOT_EQUAL(0, dht11_get_fake.return_val);
// }

// void test_light_sensor_controller()
// {
//     light_sensor_controller_init();
//     TEST_ASSERT_EQUAL(1, light_init_fake.call_count);
//     light_sensor_controller_makeReading();
//     TEST_ASSERT_EQUAL(1, light_read_fake.call_count);
//     TEST_ASSERT_NOT_NULL(light_read_fake.return_val);
// }

// void test_wifi_controller()
// {
//     wifi_controller_initialise_wifi_module();
//     TEST_ASSERT_EQUAL(1, wifi_init_fake.call_count);
//     wifi_controller_connect_to_ap();
//     TEST_ASSERT_EQUAL(1, wifi_command_join_AP_fake.call_count);
//     wifi_controller_connect_to_tcp();
//     TEST_ASSERT_EQUAL(1, wifi_command_create_TCP_connection_fake.call_count);
//     wifi_controller_send_message("Test");
//     TEST_ASSERT_EQUAL(1, wifi_command_TCP_transmit_fake.call_count);
//     TEST_ASSERT_NOT_NULL(wifi_command_TCP_transmit_fake.arg0_val);
//     TEST_ASSERT_EQUAL(50, wifi_command_TCP_transmit_fake.arg1_val);
//     wifi_controller_disconnect_from_tcp();
//     TEST_ASSERT_EQUAL(1, wifi_command_close_TCP_connection_fake.call_count);
//     wifi_controller_disconnect_from_ap();
//     TEST_ASSERT_EQUAL(1, wifi_command_quit_AP_fake.call_count);
// }

// void test_window()
// {
//     window_open();
//     TEST_ASSERT_EQUAL(1, servo_set_angle_fake.call_count);
//     TEST_ASSERT_EQUAL(180, servo_set_angle_fake.arg0_val);
//     window_close();
//     TEST_ASSERT_EQUAL(2, servo_set_angle_fake.call_count); 
//     TEST_ASSERT_EQUAL(0, servo_set_angle_fake.arg0_val);
//     window_open_at_angle(100);
//     TEST_ASSERT_EQUAL(3, servo_set_angle_fake.call_count); //ERR
//     TEST_ASSERT_EQUAL(100, servo_set_angle_fake.arg0_val);
//     int state = window_get_state();
//     TEST_ASSERT_NOT_NULL(&state); 
// }

// int main()
// {
//     UNITY_BEGIN();
//     RUN_TEST(test_debug);
//     RUN_TEST(test_decoder);
//     RUN_TEST(test_dht11_controller);
//     RUN_TEST(test_light_sensor_controller);
//     RUN_TEST(test_wifi_controller);
//     RUN_TEST(test_window);
//     return UNITY_END();
// }