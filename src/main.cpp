#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "rtos_objects.h"
#include "sensors.h"
#include "input.h"
#include "display.h"

extern "C" void app_main(void) {
    // Initialize queues and shared FreeRTOS synchronization objects
    init_rtos_objects();

    // Spawn system tasks with defined stack allocations and priority levels
    xTaskCreate(vInputTask,   "InputTask",   4096, NULL, 3, NULL);
    xTaskCreate(vSensorTask,  "SensorTask",  4096, NULL, 2, NULL);
    xTaskCreate(vMotionTask,  "MotionTask",  2048, NULL, 2, NULL);
    xTaskCreate(vDisplayTask, "DisplayTask", 4096, NULL, 1, NULL);
}