#include "sceduled_sender.h"
#include "wifiSceduler.h"
#include "periodic_task.h"


// yellow because not imported

void AppMain_Setup(){
    debug_init();
    light_sensor_controller_init();
    dht11_controller_init();
    wifiSceduler_initialise();


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