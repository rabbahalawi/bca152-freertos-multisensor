#include "rtos_objects.h"
#include "sensors.h"
#include "input.h"

QueueHandle_t displayQueue = NULL;
QueueHandle_t navQueue = NULL;

void init_rtos_objects(void) {
    displayQueue = xQueueCreate(5, sizeof(SensorData));
    navQueue = xQueueCreate(5, sizeof(NavDirection));
}