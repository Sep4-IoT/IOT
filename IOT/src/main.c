#include "display.h"
#include "pc_comm.h"
#include "includes.h"
#include "servo.h"
#include "buttons.h"
#include "periodic_task.h"
#include "window.h"
#include "debug.h"
#include "wifi_controller.h"
#include "debug.h"



 

int window_state = 1;
char message;

void button_task(); 



void setup(){
  debug_init();
  wifi_controller_initialise_wifi_module();
  //wifi_controller_set_ap_ssid("augustinas");
  //wifi_controller_set_ap_pswd("asdfghjk");
  //wifi_controller_set_server_ip("192.168.5.40");
  //wifi_controller_set_server_port(23);
  wifi_controller_connect_to_ap();
  wifi_controller_connect_to_tcp();

  display_init();
  buttons_init();
  //periodic_task_init_a(set_window,5000);
}




int main(){
  setup();
  
  display_int(1234);

  

    _delay_ms(1000);
  while (1)
  {
    
      
  }
  
}