#include "sceduled_sender.h"
#include "wifiSceduler.h"
#include "periodic_task.h"


// yellow because not imported

void AppMain_Setup(){
    window_open_at_angle(0); // Initialise window on startup to align to default position (since there's no init for it, this serves the same purpose)
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