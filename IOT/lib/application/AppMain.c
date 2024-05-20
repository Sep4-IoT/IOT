#include "sceduled_sender.h"
#include "wifiSceduler.h"
#include "periodic_task.h"

void AppMain_Setup(){
    debug_init();
    //wifiSceduler_initialise();
    wifiSceduler_initialise();
    //wifi_controller_connect_to_ap();
    //wifi_controller_connect_to_tcp();

    light_sensor_controller_init();
    dht11_controller_init();

    display_init();
    //buttons_init();
    //periodic_task_init_a(set_window,5000);

    AppMain_periodicTasks();
}

void AppMain_periodicTasks(){
    //periodic_task_init_a(wifiSceduler_RecconectionTask,5000);
    periodic_task_init_b(sceduled_sender_TaskSendAllReadings,10000);
}

void AppMain_main(){
    
    AppMain_Setup();

    while (1)
    {
        
    }

}