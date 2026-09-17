#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "rtos_objects.h"
#include "sensors.h"
#include "display.h"
#include "input.h"
#include "alarm.h"
#include "motion.h"

extern "C" void app_main() {
    // 1. Hardware Initialization 
    // (Note: Specific GPIO/I2C/ADC configurations are encapsulated inside 
    // their respective modular task files to maintain strict cohesion.)

    // 2. FreeRTOS Object Creation
    init_rtos_objects();

    // 3. Task Creation (using justified priorities from Part XII)
    xTaskCreate(vMotionTask,  "Motion Task",  2048, NULL, 3, NULL);
    xTaskCreate(vInputTask,   "Input Task",   2048, NULL, 3, NULL);
    
    xTaskCreate(vSensorTask,  "Sensor Task",  4096, NULL, 2, NULL); 
    xTaskCreate(vAlarmTask,   "Alarm Task",   2048, NULL, 2, NULL);
    
    xTaskCreate(vDisplayTask, "Display Task", 4096, NULL, 1, NULL);

    // 4. Scheduler-driven operation
    // (In native ESP-IDF, the FreeRTOS scheduler is started automatically 
    // prior to app_main(). The tasks are now running asynchronously.)
}