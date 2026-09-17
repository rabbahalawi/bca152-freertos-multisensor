#include "rtos_objects.h"
#include "sensors.h"      
#include "display.h"      
#include "system_state.h" 

// Define global handles
QueueHandle_t displayQueue = NULL;
QueueHandle_t navQueue = NULL;
EventGroupHandle_t g_systemEvents = NULL;
SemaphoreHandle_t serialMutex = NULL; // NEW: Part XI Mutex definition

void init_rtos_objects() {
    // 1. Initialize Queues
    displayQueue = xQueueCreate(10, sizeof(SensorData));
    navQueue = xQueueCreate(10, sizeof(NavDirection));

    // 2. Initialize Event Group (Part X)
    g_systemEvents = xEventGroupCreate();
    if (g_systemEvents != NULL) {
        xEventGroupSetBits(g_systemEvents, EVENT_ACTIVE);
    }

    // 3. Initialize Mutex (Part XI)
    serialMutex = xSemaphoreCreateMutex();
}