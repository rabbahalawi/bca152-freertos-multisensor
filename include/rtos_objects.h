#ifndef RTOS_OBJECTS_H
#define RTOS_OBJECTS_H

#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"

extern QueueHandle_t displayQueue;
extern QueueHandle_t navQueue;

void init_rtos_objects(void);

#endif