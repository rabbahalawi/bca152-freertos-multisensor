#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "rtos_objects.h"
#include "sensors.h"
#include "input.h"
#include "display.h"

extern "C" void app_main(void) {
    // Initialize queues first
    init_rtos_objects();

    // 4096 bytes stack prevents driver stack overflow panics[cite: 1]
    xTaskCreate(vInputTask,   "InputTask",   4096, NULL, 3, NULL);
    xTaskCreate(vSensorTask,  "SensorTask",  4096, NULL, 2, NULL);
    xTaskCreate(vDisplayTask, "DisplayTask", 4096, NULL, 1, NULL);
}